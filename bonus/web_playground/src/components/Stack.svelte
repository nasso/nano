<script lang="ts">
  export let vertical: boolean = false;
  export let fill: boolean = false;
  export let end: boolean = false;
  export let gaps: number = 0;
  export let padding: number = 0;

  $: horizontal = !vertical;
</script>

<div
  class:end
  class:fill
  class:horizontal
  class:vertical
  style={`--gaps: ${gaps}px;` + `--padding: ${padding}px;`}
>
  <slot />
</div>

<style>
  div {
    display: flex;
    gap: var(--gaps);
  }

  div.vertical {
    padding-top: var(--padding);
    padding-bottom: var(--padding);
    flex-direction: column;
  }

  div.horizontal {
    padding-left: var(--padding);
    padding-right: var(--padding);
    flex-direction: row;
  }

  div.end {
    justify-content: end;
  }

  div.fill > :global(*) {
    flex: 1 0;
  }
</style>
