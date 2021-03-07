<script lang="ts">
  import ChipPin from "./ChipPin.svelte";

  import type CustomCircuit from "@app/model";
  import type { Pin } from "@app/model";
  import type { Point } from "@app/utils";
  import type { Writable } from "svelte/store";

  import VStack from "@components/VStack.svelte";
  import { grow } from "@components/Stack.svelte";
  import ChipNode from "@components/ChipNode.svelte";
  import drag from "@components/actions/drag";
  import { writable } from "svelte/store";
  import chips from "@app/stores/chips";
  import { createEventDispatcher, tick } from "svelte";

  export let circuit: CustomCircuit;
  export let grid: number = 16;

  let chipNodes: Record<string, undefined | ChipNode> = {};

  $: {
    const garbage = Object.keys(chipNodes).filter(
      (n) => !circuit.chipsets.some((chip) => chip.name === n)
    );

    for (const name of garbage) {
      chipNodes[name] = undefined;
    }
  }

  function makeUpChipName(type: string): string {
    let i = 1;

    while (circuit.chipsets.some((c) => c.name === type + i)) {
      i++;
    }

    return type + i;
  }

  export function addChip(type: string, name: string = makeUpChipName(type)) {
    circuit.chipsets = [
      ...circuit.chipsets,
      {
        name: name,
        type: type,
        pos: { x: grid, y: grid },
      },
    ];
  }

  export function removeChip(id: number) {
    const name = circuit.chipsets[id].name;

    circuit.chipsets.splice(id, 1);
    circuit.chipsets = circuit.chipsets;

    circuit.links = circuit.links.filter(
      ({ from, to }) => from.chip !== name && to.chip !== name
    );
  }

  $: pinPos = (pin: Pin): Point => {
    if (pin.chip) {
      const chip = chipNodes[pin.chip];

      if (chip?.pinPos) {
        return chip.pinPos(pin.pin);
      }
    }

    return { x: 0, y: 0 };
  };

  function pstr(p: Point): string {
    return `${p.x},${p.y}`;
  }

  const posStoreSubs = new Map<number, Writable<Point>>();
  function posStore(chipid: number) {
    function align2d({ x, y }: Point) {
      if (grid) {
        x = Math.round(x / grid) * grid;
        y = Math.round(y / grid) * grid;
      }

      return { x, y };
    }

    return {
      subscribe(run: (p: Point) => void) {
        let store = posStoreSubs.get(chipid);

        if (!store) {
          store = writable(circuit.chipsets[chipid].pos);
          posStoreSubs.set(chipid, store);
        }

        return store.subscribe(run);
      },

      set(p: Point) {
        circuit.chipsets[chipid].pos = align2d(p);
      },
    };
  }

  let lastCircuit = circuit;

  $: if (lastCircuit !== circuit) {
    posStoreSubs.clear();
    lastCircuit = circuit;
  }

  $: circuit.chipsets.forEach((chip, i) => {
    posStoreSubs.get(i)?.set(chip.pos);
  });

  let wireSource: null | Pin = null;
  let pointerPos: Point = { x: 0, y: 0 };
</script>

<VStack gaps={8}>
  <div class="viewport" use:grow>
    <svg
      width="100%"
      height="100%"
      on:contextmenu|preventDefault
      on:pointermove={(e) => {
        pointerPos.x = e.offsetX;
        pointerPos.y = e.offsetY;
      }}
      on:pointerup={async (e) => {
        await tick();
        wireSource = null;
      }}
    >
      {#if grid}
        <defs>
          <pattern
            id={`grid-${grid}`}
            width={grid}
            height={grid}
            patternUnits="userSpaceOnUse"
          >
            <rect x="0" y="0" width="2" height="2" fill="var(--background-1)" />
          </pattern>
        </defs>

        <rect
          x="0"
          y="0"
          width="100%"
          height="100%"
          fill={`url(#grid-${grid})`}
        />
      {/if}

      {#each circuit.chipsets as chip, i}
        <g
          use:drag={{ offset: posStore(i), button: 0 }}
          on:mousedown={(e) => {
            if (e.button === 2) {
              removeChip(i);
            }
          }}
        >
          <ChipNode bind:this={chipNodes[chip.name]} bind:chip {grid} />
        </g>
        {#each [...($chips.get(chip.type)?.pinout.entries() || [])] as [pin, _]}
          <ChipPin
            pos={pinPos({ chip: chip.name, pin })}
            on:wireout={() => (wireSource = { chip: chip.name, pin })}
            on:wirein={() => {
              if (wireSource) {
                circuit.links = [
                  ...circuit.links,
                  { from: wireSource, to: { chip: chip.name, pin } },
                ];
              }
            }}
          />
        {/each}
      {/each}

      {#each circuit.links as link, i}
        <polyline
          on:mouseenter={(e) => {
            if (e.buttons === 2) {
              circuit.links.splice(i, 1);
              circuit.links = circuit.links;
            }
          }}
          class="link"
          points={`${pstr(pinPos(link.from))} ${pstr(pinPos(link.to))}`}
        />
      {/each}

      {#if wireSource}
        <polyline
          class="link wire"
          points={`${pstr(pinPos(wireSource))} ${pstr(pointerPos)}`}
        />
      {/if}
    </svg>
  </div>
</VStack>

<style lang="scss">
  .viewport {
    border-radius: 8px;
    overflow: hidden;
    background: var(--background-0);
  }

  .link {
    stroke-width: 2;
    stroke: var(--background-3);
  }

  .wire {
    pointer-events: none;
  }
</style>
