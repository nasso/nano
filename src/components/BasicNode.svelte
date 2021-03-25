<script lang="ts">
  import type { Chipset } from "@app/model";
  import type { ChipState } from "@app/nano";

  import { onMount, tick } from "svelte";

  export let width: number;
  export let height: number;
  export let minWidth: number = 0;
  export const minHeight: number = 0;
  export let chip: Chipset;
  export let state: undefined | ChipState;

  let label: SVGTextElement;

  $: {
    chip.name;
    tick().then(() => {
      minWidth = (label?.getComputedTextLength() ?? 0) + 32;
    });
  }

  onMount(() => {
    minWidth = (label?.getComputedTextLength() ?? 0) + 32;
  });
</script>

<text
  bind:this={label}
  x={width / 2}
  y={height / 2 + 2}
  text-anchor="middle"
  dominant-baseline="middle"
>
  {chip.type}
</text>

<style>
  text {
    fill: var(--foreground-2);
    font-weight: bold;
    text-transform: uppercase;
  }
</style>
