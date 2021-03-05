<script lang="ts">
  export let selected: boolean = false;
</script>

<button class:selected on:click><slot /></button>

<style lang="scss">
  button {
    margin: 0;
    background: var(--background-1);
    color: var(--foreground-1);
    padding: 8px 16px;
    border-radius: 8px;
    border: 2px solid var(--background-1);
    outline: none;

    transition: background-color 100ms;

    &:focus-visible,
    &:hover {
      background-color: var(--background-2);
    }

    &:active {
      background-color: var(--background-1);
    }
  }

  button.selected {
    background-color: var(--background-2);
    border-color: var(--background-2);

    &:hover,
    &:focus-visible {
      background-color: var(--background-3);
    }

    &:active {
      background-color: var(--background-2);
    }
  }
</style>
