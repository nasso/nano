<script lang="ts">
  import type { Align, Wrap } from "@components/Stack.svelte";
  import Stack from "@components/Stack.svelte";

  export let align: undefined | Align = undefined;
  export let wrap: undefined | Wrap = undefined;
  export let gaps: undefined | number = undefined;
  export let pad: undefined | number = undefined;
  export let hpad: undefined | number = undefined;
  export let vpad: undefined | number = undefined;
  export let inline: undefined | boolean = undefined;
  export let reverse: undefined | boolean = undefined;
  export let stretch: undefined | boolean = undefined;
</script>

<Stack
  dir="horizontal"
  {align}
  {wrap}
  {gaps}
  {pad}
  {hpad}
  {vpad}
  {inline}
  {reverse}
  {stretch}
>
  <slot />
</Stack>
