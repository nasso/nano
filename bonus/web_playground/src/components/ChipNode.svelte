<script lang="ts">
  import type { Chipset } from "@app/model/CustomCircuit";
  import type { Point } from "@app/utils";

  import chips, { PinMode } from "@app/stores/chips";

  export let chip: Chipset;
  export let grid: number;

  function gridCeil(n: number) {
    if (grid) {
      return Math.ceil(n / grid) * grid;
    } else {
      return n;
    }
  }

  $: pinout = $chips.get(chip.type)?.pinout;

  $: pins = pinout ? [...pinout.entries()] : [];
  $: inputs = pins.filter(([_, mode]) => mode === PinMode.Input);
  $: outputs = pins.filter(([_, mode]) => mode === PinMode.Output);

  const pinWidth = grid || 16;
  const pinHeight = grid || 16;

  let labelType: SVGTextElement;
  $: labelTypeWidth = labelType?.getComputedTextLength() ?? 0;

  let labelName: SVGTextElement;
  $: labelNameWidth = labelName?.getComputedTextLength() ?? 0;

  $: width = gridCeil(Math.max(labelTypeWidth, labelNameWidth) + 32);
  $: height = gridCeil(
    pinHeight * Math.max(inputs.length, outputs.length) + grid
  );

  export function pinPos(pin: number): Point {
    let pos = { x: 0, y: 0 };

    if (pinout) {
      const mode = pinout.get(pin);
      let pinList: [number, PinMode][] = pins;

      if (mode === PinMode.Input) {
        pinList = inputs;
        pos.x = -pinWidth;
      } else if (mode === PinMode.Output) {
        pinList = outputs;
        pos.x = width + pinWidth;
      }

      pos.y = (pinList.findIndex((p) => p[0] === pin) + 1) * pinHeight;
    }

    return {
      x: chip.pos.x + pos.x,
      y: chip.pos.y + pos.y,
    };
  }
</script>

<g transform={`translate(${chip.pos.x} ${chip.pos.y})`}>
  <rect class="body" x="0" y="0" {width} {height} rx="8" />

  {#each inputs as _, i}
    <line
      class="pin"
      x1={-pinWidth}
      y1={pinHeight * (i + 1)}
      x2="0"
      y2={pinHeight * (i + 1)}
    />
  {/each}

  {#each outputs as _, i}
    <line
      class="pin"
      x1={width}
      y1={pinHeight * (i + 1)}
      x2={width + pinWidth}
      y2={pinHeight * (i + 1)}
    />
  {/each}

  <text
    bind:this={labelType}
    x={width / 2}
    y={height / 2 + 2}
    text-anchor="middle"
    dominant-baseline="middle"
  >
    {chip.type}
  </text>
</g>

<style lang="scss">
  g {
    cursor: move;
  }

  .body {
    fill: var(--background-2);
  }

  .pin {
    stroke-width: 2;
    stroke: var(--background-2);
  }

  text {
    fill: var(--foreground-2);
    font-weight: bold;
    text-transform: uppercase;
  }
</style>
