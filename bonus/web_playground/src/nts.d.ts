declare namespace nts {
  export interface Deletable {
    delete(): void;
  }

  declare class Tristate {
    static readonly UNDEFINED: Tristate;
    static readonly FALSE: Tristate;
    static readonly TRUE: Tristate;
  }

  declare class PinMode {
    static readonly NONE: PinMode;
    static readonly INPUT: PinMode;
    static readonly OUTPUT: PinMode;
  }

  export interface IComponent extends Deletable {
    simulate(): void;
  }

  export interface NtsCircuit extends IComponent {
    readonly pins: Map<string, number>;
    readonly pinout: Map<string, PinMode>;
  }
}
