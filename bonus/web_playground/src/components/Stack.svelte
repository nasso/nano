<script lang="ts" context="module">
  export type Wrap = boolean | "reverse";
  export type Align = "start" | "center" | "end" | "stretch";
  export type Direction = "horizontal" | "vertical";

  export function grow(node: HTMLElement, amount: number = 1) {
    node.style.flexGrow = `${amount}`;
  }

  export function basis(node: HTMLElement, basis: string) {
    node.style.flexBasis = basis;
  }
</script>

<script lang="ts">
  import { triml } from "@app/utils";

  export let dir: Direction;
  export let align: Align = "stretch";
  export let wrap: Wrap = false;
  export let gaps: number = 0;
  export let pad: number = 0;
  export let hpad: undefined | number = undefined;
  export let vpad: undefined | number = undefined;
  export let inline: boolean = false;
  export let reverse: boolean = false;
  export let stretch: boolean = false;

  const ALIGN_VALUES = {
    start: "flex-start",
    center: "center",
    end: "flex-end",
    stretch: "stretch",
  };

  $: horizontal = dir === "horizontal";
  $: vertical = dir === "vertical";
  $: wrapMode = !wrap ? "nowrap" : wrap === true ? "wrap" : "wrap-reverse";
</script>

<div
  class:inline
  class:reverse
  class:horizontal
  class:vertical
  class:stretch
  style={triml`
    --vpad: ${vpad ?? pad}px;
    --hpad: ${hpad ?? pad}px;
    --gaps: ${gaps}px;
    --align: ${ALIGN_VALUES[align]};
    --wrap: ${wrapMode};
  `}
>
  <slot />
</div>

<style lang="scss">
  div {
    display: flex;
    padding: var(--vpad) var(--hpad);
    gap: var(--gaps);
    align-items: var(--align);
    flex-wrap: var(--wrap);

    &.stretch > :global(*) {
      flex: 1;
    }
    &.inline {
      display: inline-flex;
    }
    &.horizontal {
      flex-direction: row;
      &.reverse {
        flex-direction: row-reverse;
      }
    }
    &.vertical {
      flex-direction: column;
      &.reverse {
        flex-direction: column-reverse;
      }
    }
  }
</style>
