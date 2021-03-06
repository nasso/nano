import type { Point } from "@app/utils";
import type { Writable } from "svelte/store";

export interface Chipset {
  type: string;
  name: string;

  pos: Writable<Point>;
}

export interface Pin {
  chip?: string,
  pin: number,
}

export interface Link {
  from: Pin,
  to: Pin,
}

export default class CustomCircuit {
  chipsets: Chipset[] = [];
  links: Link[] = [];
}
