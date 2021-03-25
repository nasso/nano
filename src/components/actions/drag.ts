import type { Point } from "@app/utils";
import { get, Readable } from "svelte/store";

export interface DragOffsetStore extends Readable<Point> {
  set(value: Point): void;
}

export interface DragOptions {
  invert?: boolean;
  button?: number | number[];
  capture?: boolean;
  element?: HTMLElement | SVGElement;
  relative?: boolean;
  offset: DragOffsetStore;
}

interface Action<T> {
  update: (parameters: T) => void,
}

function isStore(v: unknown) : v is DragOffsetStore {
  return typeof v === "object" && v !== null && "subscribe" in v;
}

export default function drag(
  node: HTMLElement | SVGElement,
  storeOrOptions: DragOffsetStore | DragOptions,
): Action<DragOffsetStore | DragOptions> {
  if (isStore(storeOrOptions)) {
    return drag(node, { offset: storeOrOptions as DragOffsetStore });
  }

  let options = storeOrOptions as DragOptions;

  function handlePointerDown(this: HTMLElement | SVGElement, e: PointerEvent) {
    if (
      (typeof options.button === "number" && e.button !== options.button) ||
      (Array.isArray(options.button) && !options.button.includes(e.button))
    ) {
      return;
    }

    e.stopImmediatePropagation();
    e.preventDefault();

    const pointerStart: Point = { x: e.clientX, y: e.clientY };
    const startOffset = { ...get(options.offset) as Point };
    const elem = options.element || this;
    const capture = options.capture !== false;

    const handlePointerMove = (e: PointerEvent) => {
      const delta = {
        x: e.clientX - pointerStart.x,
        y: e.clientY - pointerStart.y,
      };

      if (options.relative) {
        pointerStart.x = e.clientX;
        pointerStart.y = e.clientY;
      }

      const factor = options.invert ? -1 : 1;

      options.offset.set({
        x: startOffset.x + delta.x * factor,
        y: startOffset.y + delta.y * factor,
      });
    };

    const handlePointerUp = (e: PointerEvent): void => {
      if (options.relative) {
        options.offset.set({
          x: startOffset.x,
          y: startOffset.y,
        });
      }

      if (elem instanceof HTMLElement) {
        elem.removeEventListener("pointermove", handlePointerMove);
        elem.removeEventListener("pointerup", handlePointerUp);
      } else if (elem instanceof SVGElement) {
        elem.removeEventListener("pointermove", handlePointerMove);
        elem.removeEventListener("pointerup", handlePointerUp);
      }

      if (capture) {
        elem.releasePointerCapture(e.pointerId);
      }

      this.dispatchEvent(new CustomEvent("dragend"));
    };

    if (elem instanceof HTMLElement) {
      elem.addEventListener("pointermove", handlePointerMove);
      elem.addEventListener("pointerup", handlePointerUp);
    } else if (elem instanceof SVGElement) {
      elem.addEventListener("pointermove", handlePointerMove);
      elem.addEventListener("pointerup", handlePointerUp);
    }

    if (capture) {
      elem.setPointerCapture(e.pointerId);
    }

    this.dispatchEvent(new CustomEvent("dragstart"));
  }

  if (node instanceof HTMLElement) {
    node.addEventListener("pointerdown", handlePointerDown);
  } else if (node instanceof SVGElement) {
    node.addEventListener("pointerdown", handlePointerDown);
  }

  return {
    update(newParams) {
      if (isStore(newParams)) {
        options = { offset: newParams };
      } else {
        options = newParams;
      }
    },
  };
}
