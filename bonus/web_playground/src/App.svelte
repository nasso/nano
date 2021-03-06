<script lang="ts">
  import type { NtsModule } from "@app/nts";
  import CustomCircuit from "@app/model/CustomCircuit";
  import CircuitEditor from "@components/CircuitEditor.svelte";
  import { onDestroy, setContext } from "svelte";
  import VStack from "@components/VStack.svelte";
  import HStack from "@components/HStack.svelte";
  import Button from "@components/Button.svelte";
  import Grow from "@components/Grow.svelte";

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

  interface Editor {
    name: string;
    circuit: CustomCircuit;
  }

  let editors: Editor[] = [];
  let currentEditor = 0;

  function newCircuit(name?: string) {
    function makeUpNewName() {
      let i = 1;

      while (editors.some((e) => e.name === `untitled_${i}`)) {
        i++;
      }

      return `untitled_${i}`;
    }

    editors = [
      ...editors,
      {
        name: name ?? makeUpNewName(),
        circuit: new CustomCircuit(),
      },
    ];
  }

  newCircuit();
  newCircuit();

  onDestroy(async () => {
    mainFactory.delete();
  });
</script>

<main>
  <VStack pad={8} gaps={8}>
    <HStack align="start" gaps={8}>
      <HStack wrap="reverse" stretch gaps={8}>
        {#each editors as editor, i}
          <Button
            selected={i === currentEditor}
            on:click={() => (currentEditor = i)}
          >
            {editor.name}
          </Button>
        {/each}
      </HStack>
      <Grow />
      <Button on:click={() => newCircuit()}>+</Button>
    </HStack>
    <Grow>
      <CircuitEditor bind:circuit={editors[currentEditor].circuit} />
    </Grow>
  </VStack>
</main>

<style>
  main {
    display: grid;
    height: 100%;
  }
</style>
