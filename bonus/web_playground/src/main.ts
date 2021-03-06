import App from "@app/App.svelte";
import nano from "@app/nano";

async function main() {
  const nts = await nano;

  new App({
    target: document.body,
    props: { nts },
  });
}

main();
