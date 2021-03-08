import type { Circuit as UserCircuit } from "@app/model";
import { PinMode } from "@app/stores/chips.js";
import createNts, {
  ComboComponentFactory,
  NtsModule,
  Circuit,
  PinId,
  Tristate,
} from "./nts.js";

const nano = createNts({
  locateFile(path: string): string {
    return `${path}`;
  },
});

export type SimulationState = Map<string, Map<PinId, undefined | boolean>>;

export class Simulator {
  #nts: NtsModule;
  #factory: ComboComponentFactory;
  #pins: Map<string, PinId>;
  #circuit: Circuit;

  static async create(circuit: UserCircuit): Promise<Simulator> {
    return new Simulator(await nano, circuit);
  }

  constructor(nts: NtsModule, circuit: UserCircuit) {
    console.log("Setting up factories...");

    this.#nts = nts;
    this.#factory = new nts.ComboComponentFactory();

    const builtinFactory = new nts.BuiltInComponentFactory();
    this.#factory.add(builtinFactory);

    console.log("Constructing circuit...");

    this.#circuit = new nts.Circuit();
    this.#pins = new Map();

    console.log(this.#circuit);

    let pinCounter: PinId = 0;

    for (const chip of circuit.chipsets) {
      if (chip.type === "input") {
        pinCounter++;
        this.#circuit.pinMode(pinCounter, PinMode.Input);
        this.#pins.set(chip.name, pinCounter);
      } else if (chip.type === "output") {
        pinCounter++;
        this.#circuit.pinMode(pinCounter, PinMode.Output);
        this.#pins.set(chip.name, pinCounter);
      } else {
        const comp = this.#factory.createComponent(chip.type);

        if (comp) {
          this.#circuit.insert(chip.name, comp);
        } else {
          this.#circuit.delete();
          this.#factory.delete();
          throw new Error(`Couldn't create chip: ${chip.name}`);
        }
      }
    }

    for (const { from, to } of circuit.links) {
      if (from.chip && to.chip) {
        const frompin = this.#pins.get(from.chip);
        const topin = this.#pins.get(to.chip);

        if (frompin && topin) {
          this.#circuit.connect(frompin, topin);
        } else if (frompin) {
          this.#circuit.connect(frompin, to.chip, to.pin);
        } else if (topin) {
          this.#circuit.connect(topin, from.chip, from.pin);
        } else {
          this.#circuit.connect(from.chip, from.pin, to.chip, to.pin);
        }
      }
    }

    /*
    {
      const creationStack = new Set<string>();

      mainFactory.add(
        nts.IComponentFactory.implement({
          createComponent(name: string) {
            if (creationStack.has(name)) {
              console.log("circular dependency!");
              return;
            }

            let chip = chips.find((v) => name === v.name);

            if (chip) {
              creationStack.add(chip.name);
              let circuit = null;
              try {
                circuit = new nts.NtsCircuit(chip.source, mainFactory);
              } catch (_) {}
              creationStack.delete(chip.name);
              return circuit;
            }
          },
        })
      );
    }
    */
  }

  tick(): void {
    this.#circuit.tick();
  }

  inspect(state: SimulationState, chips: string[]): void {
    state.clear();

    const normalChips = chips
      .map((name) => {
        if (this.#pins.has(name)) {
          return { pin: this.#pins.get(name), name };
        } else {
          return { chip: this.#circuit.get(name), name };
        }
      });

    for (const { chip, pin, name } of normalChips) {
      if (pin !== undefined) {
        state.set(name, new Map([[1, this.tri(this.#circuit.read(pin))]]));
      } else if (chip !== undefined) {
        const pinout = new Map<PinId, undefined | boolean>();
        const pins = chip.pinout().keys();

        for (let i = 0; i < pins.size(); i++) {
          const pin = pins.get(i);

          pinout.set(pin, this.tri(chip.read(pin)));
        }

        state.set(name, pinout);
      }
    }
  }

  tri(t: Tristate): undefined | boolean {
    if (t === this.#nts.Tristate.TRUE) {
      return true;
    } else if (t === this.#nts.Tristate.FALSE) {
      return false;
    }
  }

  delete(): void {
    this.#circuit.delete();
    this.#factory.delete();
    console.log("Deleted simulator");
  }
}

export default nano;
