<script lang="ts">
  import { grow } from "@components/Stack.svelte";
</script>

<div use:grow>
  <slot />
</div>

<style>
  div {
    display: grid;
  }
</style>
