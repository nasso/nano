<script lang="ts">
  import type { Point } from "@app/utils";

  import { createEventDispatcher } from "svelte";

  export let pos: Point;

  const dispatch = createEventDispatcher();
</script>

<g
  on:pointerdown={(e) => e.button === 0 && dispatch("wireout")}
  on:pointerup={(e) => e.button === 0 && dispatch("wirein")}
>
  <circle class="pin" cx={pos.x} cy={pos.y} r="4" />
  <circle class="hotspot" cx={pos.x} cy={pos.y} r="8" />
</g>

<style>
  .pin {
    fill: var(--background-2);
    opacity: 0;
  }

  .hotspot {
    visibility: hidden;
  }

  g {
    pointer-events: all;
  }

  g:hover .pin {
    opacity: 1;
  }
</style>
