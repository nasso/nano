<script lang="ts">
  import type { ChipInfo } from "@app/stores/chips";
  import type { SimulationState } from "@app/nano";

  import { PinMode } from "@app/stores/chips";
  import { Circuit } from "@app/model";
  import CircuitEditor from "@components/CircuitEditor.svelte";
  import { onDestroy } from "svelte";
  import VStack from "@components/VStack.svelte";
  import HStack from "@components/HStack.svelte";
  import Button from "@components/Button.svelte";
  import Grow from "@components/Grow.svelte";
  import ChipPicker from "@components/ChipPicker.svelte";
  import chips from "@app/stores/chips";
  import { Simulator } from "@app/nano";

  interface UserCircuit {
    name: string;
    circuit: Circuit;
    state: SimulationState;
    simulator?: Simulator;
  }

  let editor: CircuitEditor;
  let showPicker = false;

  let userCircuits: UserCircuit[] = [];
  let currentCircuitId = 0;

  let currentCircuit: undefined | UserCircuit;
  $: currentCircuit = userCircuits[currentCircuitId];

  function updatePinout({ name, circuit }: UserCircuit) {
    chips.update((chips) => {
      if (!chips.has(name)) {
        chips.set(name, { pinout: new Map() });
      }

      const chip = chips.get(name) as ChipInfo;

      chip.pinout.clear();

      circuit.chipsets
        .filter((chip) => ["input", "output"].includes(chip.type))
        .forEach(({ type }, i) => {
          if (type === "input") {
            chip.pinout.set(i, PinMode.Input);
          } else if (type === "output") {
            chip.pinout.set(i, PinMode.Output);
          }
        });

      return chips;
    });
  }

  function addInput() {
    editor.addChip("input");

    if (currentCircuit) {
      updatePinout(currentCircuit);
    }
  }

  function addOutput() {
    editor.addChip("output");

    if (currentCircuit) {
      updatePinout(currentCircuit);
    }
  }

  function newCircuit(name?: string) {
    function makeUpNewName() {
      let i = 1;

      while (userCircuits.some((e) => e.name === `untitled_${i}`)) {
        i++;
      }

      return `untitled_${i}`;
    }

    const editorName = name ?? makeUpNewName();

    if ($chips.has(editorName)) {
      throw new Error("The circuit name isn't unique");
    }

    let editor: UserCircuit = {
      name: editorName,
      circuit: new Circuit(),
      state: new Map(),
    };

    userCircuits = [...userCircuits, editor];

    chips.update((chips) => {
      chips.set(editor.name, { pinout: new Map() });
      return chips;
    });
  }

  {
    const localSave = window.localStorage.getItem("circuits");

    if (localSave) {
      const save = JSON.parse(localSave);

      userCircuits = save;

      for (const circuit of userCircuits) {
        circuit.state = new Map();
        updatePinout(circuit);
      }
    } else {
      newCircuit();
    }
  }

  let timeout: undefined | number = undefined;
  $: {
    if (timeout) {
      clearTimeout(timeout);
    }

    timeout = setTimeout(() => {
      window.localStorage.setItem(
        "circuits",
        JSON.stringify(
          userCircuits.map(({ name, circuit }) => ({
            name,
            circuit,
          }))
        )
      );
    }, 1000);
  }

  $: chipLibrary = [
    "and",
    "not",
    ...userCircuits.filter((_, i) => i !== currentCircuitId).map((e) => e.name),
  ];

  function updateState() {
    if (currentCircuit && currentCircuit.simulator) {
      currentCircuit.state = currentCircuit.simulator.inspect(
        currentCircuit.circuit.chipsets.map(({ name }) => name)
      );
    }
  }

  async function compile() {
    if (currentCircuit) {
      currentCircuit.simulator?.delete();
      currentCircuit.simulator = undefined;

      currentCircuit.simulator = await Simulator.create(currentCircuit.circuit);

      if (currentCircuit.state) {
        for (const [name, chip] of currentCircuit.state.entries()) {
          for (const [pin, value] of chip) {
            currentCircuit.simulator.set(name, pin, value);
          }
        }
      }

      updateState();
    }
  }

  function setPinValue(
    chipname: string,
    pin: number,
    value: undefined | boolean
  ) {
    if (currentCircuit?.simulator) {
      currentCircuit.simulator.set(chipname, pin, value);

      updateState();
    } else if (currentCircuit) {
      let chip = currentCircuit.state.get(chipname);

      if (!chip) {
        chip = new Map();
        currentCircuit.state.set(chipname, chip);
      }

      chip.set(pin, value);

      currentCircuit.state = currentCircuit.state;
    }
  }

  function simulate() {
    if (currentCircuit?.simulator) {
      currentCircuit.simulator.simulate();

      updateState();
    }
  }

  function tick() {
    if (currentCircuit?.simulator) {
      currentCircuit.simulator.tick();

      updateState();
    }
  }

  onDestroy(async () => {
    for (const circuit of userCircuits) {
      circuit.simulator?.delete();
    }
  });
</script>

<main>
  <VStack pad={8} gaps={8}>
    <HStack align="start" gaps={8}>
      <HStack wrap="reverse" stretch gaps={8}>
        {#each userCircuits as circuit, i}
          <Button
            selected={i === currentCircuitId}
            on:click={() => (currentCircuitId = i)}
          >
            {circuit.name}
          </Button>
        {/each}
      </HStack>
      <Button on:click={() => newCircuit()}>+</Button>
    </HStack>
    <Grow>
      {#if currentCircuit}
        <!-- TODO fix issues that force us to recreate the editor every time -->
        {#key currentCircuit.name}
          <CircuitEditor
            bind:this={editor}
            bind:circuit={currentCircuit.circuit}
            state={currentCircuit.state}
            on:setpin={({ detail: { chip, pin, value } }) => {
              setPinValue(chip, pin, value);
            }}
          />
        {/key}
      {/if}
    </Grow>

    <HStack stretch gaps={8}>
      <Button on:click={() => addInput()}>Add input</Button>
      <Button on:click={() => (showPicker = true)}>Add chip</Button>
      <Button on:click={() => addOutput()}>Add output</Button>
      <Grow />
      <Button on:click={compile} disabled={!currentCircuit}>Compile</Button>
      <Button disabled={!currentCircuit?.simulator} on:click={simulate}>
        Simulate
      </Button>
      <Button disabled={!currentCircuit?.simulator} on:click={tick}>
        Tick
      </Button>
    </HStack>

    <div class="picker" class:show={showPicker}>
      <ChipPicker
        chips={chipLibrary}
        on:cancel={() => (showPicker = false)}
        on:pick={(e) => {
          editor.addChip(e.detail);
          showPicker = false;
        }}
      />
    </div>
  </VStack>
</main>

<style lang="scss">
  main {
    display: grid;
    height: 100%;
  }

  .picker {
    position: fixed;
    left: 50%;
    bottom: 0;
    transform: translate(-50%, 100%);

    transition: transform 300ms;

    &.show {
      transform: translate(-50%, 0%);
    }
  }
</style>
