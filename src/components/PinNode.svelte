<script lang="ts">
  import type { Chipset } from "@app/model";
  import type { ChipState } from "@app/nano";

  import { createEventDispatcher, onMount, tick } from "svelte";

  const PADDING = 16;
  const SPACING = 8;
  const BUTTON_RADIUS = 6;

  const dispatch = createEventDispatcher();

  export let width: number;
  export let height: number;
  export let minWidth: number = 0;
  export const minHeight: number = 0;
  export let chip: Chipset;
  export let state: undefined | ChipState;

  let label: SVGTextElement;

  function computeMinWidth() {
    minWidth =
      (label?.getComputedTextLength() ?? 0) +
      SPACING +
      BUTTON_RADIUS * 2 +
      PADDING * 2;
  }

  $: {
    chip.name;
    tick().then(computeMinWidth);
  }

  $: isInput = chip.type === "input";
  $: pinValue = state?.get(1);

  function toggleValue() {
    dispatch("setpin", { pin: 1, value: !pinValue });
  }

  onMount(computeMinWidth);
</script>

<text
  bind:this={label}
  x={isInput ? PADDING : width - PADDING}
  y={height / 2 + 2}
  text-anchor={isInput ? "start" : "end"}
  dominant-baseline="middle"
>
  {chip.name}
</text>
<circle
  cx={isInput ? width - PADDING - BUTTON_RADIUS : PADDING + BUTTON_RADIUS}
  cy={height / 2}
  r={BUTTON_RADIUS}
  fill={pinValue === undefined
    ? "var(--pin-value-undefined)"
    : pinValue
    ? "var(--pin-value-true)"
    : "var(--pin-value-false)"}
/>
<rect
  x={isInput ? width - PADDING - BUTTON_RADIUS * 2 - SPACING : 0}
  y={0}
  width={PADDING + BUTTON_RADIUS * 2 + SPACING}
  {height}
  fill="transparent"
  on:click={toggleValue}
/>

<style>
  text {
    fill: var(--foreground-2);
    font-weight: bold;
    text-transform: uppercase;
  }

  rect {
    cursor: default;
  }
</style>
