import createNts from "./nts.js";
import App from "@components/App.svelte";

createNts({
  locateFile(path: string): string {
    return `${path}`;
  },
}).then((nts) => {
  new App({
    target: document.body,
    props: { nts },
  });
});
