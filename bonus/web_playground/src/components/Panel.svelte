<div>
  <slot />
</div>

<style>
  div {
    margin: 0;
    background: var(--background-1);
    color: var(--foreground-1);
    padding: 16px;
    border-radius: 8px;
    border: 2px solid var(--background-1);

    transition: border-color 30ms;
  }

  div:focus-within {
    outline: none;
    border-color: var(--background-2);
  }
</style>
