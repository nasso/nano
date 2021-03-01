<script lang="ts">
  import { tick } from "svelte";
  import Panel from "@components/Panel.svelte";

  export let text: string = "";

  let area = null;

  async function updateHeight() {
    await tick();
    if (area) {
      area.style.height = "5px";
      area.style.height = `${area.scrollHeight}px`;
    }
  }

  $: {
    text;
    updateHeight();
  }
</script>

<Panel>
  <textarea bind:this={area} bind:value={text} />
</Panel>

<style>
  textarea {
    outline: none;
    background: none;
    border: none;
    color: inherit;

    resize: none;
    overflow: hidden;
    min-height: 50px;
    width: 100%;
  }
</style>
