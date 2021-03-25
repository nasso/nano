/* eslint-disable @typescript-eslint/explicit-module-boundary-types */
/* eslint-disable @typescript-eslint/no-var-requires */
/* eslint-disable no-undef */

const { spawn } = require("child_process");

const docker = spawn("docker", [
  "run", "--rm",
  "-v", `${__dirname}:/code`,
  "-w", "/code",
  "emscripten/emsdk",
  "./build.sh",
]);

docker.stdout.on("data", data => {
  process.stdout.write(data);
});

docker.stderr.on("data", data => {
  process.stderr.write(data);
});

process.stdin.on("data", data => {
  docker.stdin.write(data);
});

docker.on("error", error => {
  console.warn(`error: ${error.message}`);
});

docker.on("close", code => {
  process.exit(code);
});
