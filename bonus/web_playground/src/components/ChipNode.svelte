<script lang="ts">
  import type { Chipset } from "@app/model/CustomCircuit";

  export let chip: Chipset;

  $: pos = chip.pos;
</script>

<rect x={$pos.x} y={$pos.y} width="100" height="100" fill="red" />
