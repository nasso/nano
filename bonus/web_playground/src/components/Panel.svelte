<script lang="ts">
  export let padding: number = 16;
</script>

<div style={`--padding: ${padding}px`}>
  <slot />
</div>

<style>
  div {
    background: var(--background-1);
    color: var(--foreground-1);
    padding: var(--padding);
    border: 2px solid var(--background-1);
    border-radius: 8px;
    margin: 0;

    transition: border-color 30ms;
  }

  div:focus-within {
    outline: none;
    border-color: var(--background-2);
  }
</style>
