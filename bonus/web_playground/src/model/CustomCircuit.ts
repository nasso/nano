import type { Point } from "@app/utils";

export interface Chipset {
  type: string;
  name: string;

  pos: Point;
}

export interface Pin {
  chip?: Chipset,
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
