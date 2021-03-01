import createNts from "/nts.js";
import App from "@components/App.svelte";

createNts().then((nts) => {
  new App({
    target: document.body,
    props: { nts },
  });
});
