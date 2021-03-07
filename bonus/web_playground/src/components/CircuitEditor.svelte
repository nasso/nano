<script lang="ts">
  import ChipPin from "./ChipPin.svelte";

  import type CustomCircuit, { Link } from "@app/model/CustomCircuit";
  import type { Pin } from "@app/model/CustomCircuit";
  import type { Point } from "@app/utils";
  import type { get, Writable } from "svelte/store";

  import { us } from "@app/utils";
  import VStack from "@components/VStack.svelte";
  import Button from "@components/Button.svelte";
  import { grow } from "@components/Stack.svelte";
  import ChipNode from "@components/ChipNode.svelte";
  import drag from "@components/actions/drag";
  import { writable } from "svelte/store";
  import chips from "@app/stores/chips";
  import { tick } from "svelte";
  import App from "@app/App.svelte";

  export let circuit: CustomCircuit;
  export let grid: number = 16;

  let chipNodes: Record<string, ChipNode> = {};

  function makeUpChipName(type: string): string {
    let i = 1;

    while (circuit.chipsets.some((c) => c.name === type + i)) {
      i++;
    }

    return type + i;
  }

  function addChip(type: string, name: string = makeUpChipName(type)) {
    circuit.chipsets = [
      ...circuit.chipsets,
      {
        name: name,
        type: type,
        pos: { x: 100, y: 200 },
      },
    ];
  }

  function removeChip(id: number) {
    circuit.chipsets.splice(id, 1);
    circuit.chipsets = circuit.chipsets;
  }

  function pinPos(pin: Pin): Point {
    if (pin.chip) {
      const chip = chipNodes[pin.chip.name];

      if (chip) {
        return chip.pinPos(pin.pin);
      }
    }

    return { x: 0, y: 0 };
  }

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

  addChip("and", "and1");
  addChip("not", "not1");

  circuit.chipsets[0].pos = { x: 300, y: 100 };
  circuit.links = [
    {
      from: {
        chip: circuit.chipsets[0],
        pin: 3,
      },
      to: {
        chip: circuit.chipsets[1],
        pin: 1,
      },
    },
  ];
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

      {#each circuit.chipsets as chip, i}
        <g use:drag={posStore(i)}>
          <ChipNode bind:this={chipNodes[chip.name]} bind:chip {grid} />
        </g>
        {#each [...($chips.get(chip.type)?.pinout.entries() || [])] as [pin, _]}
          <ChipPin
            pos={pinPos({ chip, pin })}
            on:wireout={() => (wireSource = { chip, pin })}
            on:wirein={() => {
              if (wireSource) {
                circuit.links = [
                  ...circuit.links,
                  { from: wireSource, to: { chip, pin } },
                ];
              }
            }}
          />
        {/each}
      {/each}

      {#if wireSource}
        <polyline
          class="link wire"
          points={`${pstr(pinPos(wireSource))} ${pstr(pointerPos)}`}
        />
      {/if}
    </svg>
  </div>
  <Button on:click={() => addChip("and")}>Add chip</Button>
</VStack>

<style lang="scss">
  .viewport {
    border-radius: 8px;
    overflow: hidden;
    background: var(--background-0);
  }

  .link {
    stroke-width: 2;
    stroke: var(--background-2);
  }

  .wire {
    pointer-events: none;
  }
</style>
