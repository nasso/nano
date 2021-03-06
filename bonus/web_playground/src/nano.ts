import createNts from "./nts.js";

const nano = createNts({
  locateFile(path: string): string {
    return `${path}`;
  },
});

export default nano;
