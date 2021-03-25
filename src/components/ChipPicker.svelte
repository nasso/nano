<script lang="ts">
  import { createEventDispatcher } from "svelte";
  import Button from "@components/Button.svelte";
  import VStack from "@components/VStack.svelte";

  export let chips: string[];

  const dispatch = createEventDispatcher();
</script>

<div>
  <VStack gaps={8} pad={8}>
    {#each chips as chipname}
      <Button on:click={() => dispatch("pick", chipname)}>{chipname}</Button>
    {/each}
    <Button on:click={() => dispatch("cancel")}>V</Button>
  </VStack>
</div>

<style>
  div {
    background: var(--background-0);
    border: 2px solid var(--background-2);
    border-bottom: none;
    border-radius: 16px 16px 0px 0px;
    width: 25vw;
    max-height: 75vh;
    overflow-y: auto;
    scrollbar-width: none;
  }
</style>
