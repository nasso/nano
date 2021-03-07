<script lang="ts">
  import type { NtsModule } from "@app/nts";
  import type { ChipInfo } from "@app/stores/chips";

  import { PinMode } from "@app/stores/chips";
  import Circuit from "@app/model";
  import CircuitEditor from "@components/CircuitEditor.svelte";
  import { onDestroy, setContext } from "svelte";
  import VStack from "@components/VStack.svelte";
  import HStack from "@components/HStack.svelte";
  import Button from "@components/Button.svelte";
  import Grow from "@components/Grow.svelte";
  import ChipPicker from "@components/ChipPicker.svelte";
  import chips from "@app/stores/chips";

  export let nts: NtsModule;
  setContext("nts", nts);

  const mainFactory = new nts.ComboComponentFactory();

  {
    const builtinFactory = new nts.BuiltInComponentFactory();
    mainFactory.add(builtinFactory);
  }

  {
    const creationStack = new Set<string>();

    mainFactory.add(
      nts.IComponentFactory.implement({
        createComponent(name: string) {
          if (creationStack.has(name)) {
            console.log("circular dependency!");
            return;
          }

          /*
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
          */
        },
      })
    );
  }

  interface UserCircuit {
    name: string;
    circuit: Circuit;
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
      window.localStorage.setItem("circuits", JSON.stringify(userCircuits));
    }, 1000);
  }

  $: chipLibrary = [
    "and",
    "not",
    ...userCircuits.filter((_, i) => i !== currentCircuitId).map((e) => e.name),
  ];

  onDestroy(async () => {
    mainFactory.delete();
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
          />
        {/key}
      {/if}
    </Grow>
    <HStack stretch gaps={8}>
      <Button on:click={() => addInput()}>Add input</Button>
      <Button on:click={() => (showPicker = true)}>Add chip</Button>
      <Button on:click={() => addOutput()}>Add output</Button>
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
