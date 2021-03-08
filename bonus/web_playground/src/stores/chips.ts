import type { SvelteComponent } from "svelte";
import { Writable, writable } from "svelte/store";
import InputNode from "@components/InputNode.svelte";

export enum PinMode {
  None = 0,
  Input = 1,
  Output = 2,
  IO = Input | Output,
}

export interface ChipInfo {
  pinout: Map<number, PinMode>,
  view?: typeof SvelteComponent,
}

const chips: Writable<Map<string, ChipInfo>> = writable(new Map([
  ["input", {
    pinout: new Map([[1, PinMode.Output]]),
    view: InputNode,
  }],
  ["output", {
    pinout: new Map([[1, PinMode.Input]]),
  }],
  ["and", {
    pinout: new Map([
      [1, PinMode.Input],
      [2, PinMode.Input],
      [3, PinMode.Output],
    ]),
  }],
  ["not", {
    pinout: new Map([
      [1, PinMode.Input],
      [2, PinMode.Output],
    ]),
  }],
]));

export default chips;
