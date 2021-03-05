<script lang="ts">
  import Button from "@components/Button.svelte";
  import NtsEditor from "@components/NtsEditor.svelte";
  import Panel from "@components/Panel.svelte";
  import Stack from "@components/Stack.svelte";

  export let nts;

  let chips = [
    {
      name: "nor",
      source:
        "# NOR gate\n" +
        "\n" +
        ".chipsets:\n" +
        "input a\n" +
        "input b\n" +
        "output out\n" +
        "not not_a\n" +
        "not not_b\n" +
        "and and\n" +
        "\n" +
        ".links:\n" +
        "a:1 not_a:1\n" +
        "b:1 not_b:1\n" +
        "not_a:2 and:1\n" +
        "not_b:2 and:2\n" +
        "and:3 out:1",
    },
  ];

  const mainFactory = new nts.ComboComponentFactory();

  {
    const builtinFactory = new nts.BuiltInComponentFactory();
    mainFactory.add(builtinFactory);
  }

  {
    const creationStack = new Set<string>();

    mainFactory.add(
      nts.IComponentFactory.implement({
        createComponent(name: string) {
          if (creationStack.has(name)) {
            console.log("circular dependency!");
            return;
          }

          let chip = chips.find((v) => name === v.name);

          if (chip) {
            creationStack.add(chip.name);
            const circuit = new nts.NtsCircuit(chip.source, mainFactory);
            creationStack.delete(chip.name);
            return circuit;
          }
        },
      })
    );
  }

  let currentChip = 0;

  function newChip() {
    const name = prompt("Chip name");

    if (name) {
      chips = [
        ...chips,
        {
          name,
          source:
            `# ${name}\n` +
            "\n" +
            ".chipsets:\n" +
            "input a\n" +
            "input b\n" +
            "output out\n" +
            "\n" +
            ".links:\n",
        },
      ];

      currentChip = chips.length - 1;
    }
  }

  let stable = false;
  let circuit = null;
  let inputs: Record<string, undefined | boolean> = {};
  let outputs: Record<string, undefined | boolean> = {};

  function readPins(filter) {
    if (!circuit) {
      return;
    }

    const pinValues = {};

    const pins = circuit.pins;
    const pinout = circuit.pinout;
    const pinNames = pins.keys();
    const pinCount = pinNames.size();

    for (let i = 0; i < pinCount; i++) {
      const name = pinNames.get(i);
      const id = pins.get(name);
      const value = circuit.read(id);
      let triVal = undefined;

      switch (value) {
        case nts.Tristate.FALSE:
          triVal = false;
          break;
        case nts.Tristate.TRUE:
          triVal = true;
          break;
      }

      if (pinout.get(id) == filter) {
        pinValues[name] = triVal;
      }
    }

    return pinValues;
  }

  function compile() {
    if (circuit) {
      circuit.delete();
      circuit = null;
    }

    try {
      circuit = new nts.NtsCircuit(chips[currentChip].source, mainFactory);
      inputs = readPins(nts.PinMode.INPUT);
      outputs = readPins(nts.PinMode.OUTPUT);
    } catch (e) {
      console.log(e);
    }
  }

  function writeInputs() {
    if (circuit) {
      for (const key of Object.keys(inputs)) {
        const id = circuit.pins.get(key);

        switch (inputs[key]) {
          case undefined:
            circuit.write(id, nts.Tristate.UNDEFINED);
            break;
          case false:
            circuit.write(id, nts.Tristate.FALSE);
            break;
          case true:
            circuit.write(id, nts.Tristate.TRUE);
            break;
        }
      }
    }
  }

  function tick() {
    if (!circuit) {
      compile();
    }

    if (circuit) {
      writeInputs();

      circuit.tick();
      stable = circuit.stable;
      outputs = readPins(nts.PinMode.OUTPUT);
    }
  }

  function stabilize() {
    const maxTicks = 100;

    if (!circuit) {
      compile();
    }

    if (circuit) {
      writeInputs();

      stable = circuit.stable;

      for (let i = 0; i < maxTicks && !stable; i++) {
        circuit.tick();
        stable = circuit.stable;
      }

      outputs = readPins(nts.PinMode.OUTPUT);
    }
  }
</script>

<main>
  <Stack vertical gaps={8} padding={8}>
    <Stack gaps={8}>
      {#each chips as chip, i}
        <Button selected={currentChip == i} on:click={() => (currentChip = i)}>
          {chip.name}
        </Button>
      {/each}
      <Button on:click={newChip}>+</Button>
    </Stack>
    <NtsEditor bind:text={chips[currentChip].source} />
    <Stack fill gaps={8}>
      <Stack vertical gaps={8}>
        <Button on:click={compile}>Compile</Button>
        <Panel>
          {#each Object.keys(inputs) as key}
            <div class="input">
              <label>
                {key}
                <select name={key} bind:value={inputs[key]}>
                  <option value={undefined}>UNDEFINED</option>
                  <option value={false}>FALSE</option>
                  <option value={true}>TRUE</option>
                </select>
              </label>
            </div>
          {/each}
        </Panel>
      </Stack>
      <Stack vertical gaps={8}>
        <Stack fill gaps={8}>
          <Button on:click={tick}>Tick</Button>
          <Button on:click={stabilize}>Stabilize</Button>
        </Stack>
        <Panel>
          {#each Object.keys(outputs) as key}
            <pre>{key} = {`${outputs[key]}`}</pre>
          {/each}
          {#if circuit && !stable}
            <pre>Circuit is unstable!</pre>
          {/if}
        </Panel>
      </Stack>
    </Stack>
  </Stack>
</main>

<style>
  pre {
    margin: 0;
    padding: 0;
  }

  .input select {
    float: right;
  }
</style>
