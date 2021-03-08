<script lang="ts">
  export let selected: boolean = false;
  export let disabled: boolean = false;
</script>

<button class:selected {disabled} on:click on:dblclick><slot /></button>

<style lang="scss">
  button {
    --button-bg: var(--background-1);
    --button-fg: var(--foreground-1);

    margin: 0;
    background: var(--button-bg);
    color: var(--button-fg);
    padding: 8px 16px;
    border: none;
    border-radius: 8px;
    outline: none;

    transition: background-color 100ms, opacity 100ms;

    &:hover,
    &:focus-visible {
      --button-bg: var(--background-2);
      --button-fg: var(--foreground-2);
    }

    &.selected,
    &:active {
      --button-bg: var(--background-0);
      --button-fg: var(--foreground-0);
    }

    &[disabled] {
      opacity: 0.5;
      pointer-events: none;
    }
  }
</style>
