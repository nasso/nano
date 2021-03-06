<script lang="ts">
  import type CustomCircuit from "@app/model/CustomCircuit";

  import VStack from "@components/VStack.svelte";
  import Button from "@components/Button.svelte";
  import { grow } from "@components/Stack.svelte";
  import ChipNode from "@components/ChipNode.svelte";
  import drag from "@components/actions/drag";
  import { readable, writable } from "svelte/store";

  export let circuit: CustomCircuit;

  function addChip() {
    circuit.chipsets = [
      ...circuit.chipsets,
      {
        name: "chip",
        type: "and",
        pos: writable({ x: 100, y: 200 }),
      },
    ];
  }

  function removeChip(id: number) {
    circuit.chipsets.splice(id, 1);
    circuit.chipsets = circuit.chipsets;
  }

  addChip();
</script>

<VStack gaps={8}>
  <div class="viewport" use:grow>
    <svg width="100%" height="100%">
      {#each circuit.chipsets as chip, i}
        <g use:drag={{ offset: chip.pos }}>
          <ChipNode bind:chip />
        </g>
      {/each}
    </svg>
  </div>
  <Button on:click={addChip}>Add chip</Button>
</VStack>

<style>
  .viewport {
    border-radius: 8px;
    overflow: hidden;
    background: var(--background-0);
  }
</style>
