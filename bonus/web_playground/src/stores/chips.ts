import { Writable, writable } from "svelte/store";

export enum PinMode {
  None = 0,
  Input = 1,
  Output = 2,
  IO = Input | Output,
}

export interface ChipInfo {
  pinout: Map<number, PinMode>,
}

const chips: Writable<Map<string, ChipInfo>> = writable(new Map([
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
