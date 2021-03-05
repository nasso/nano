# NanoTekSpice

The NanoTekSpice is a digital logic simulator. It is a second year project at
[Epitech].

## Building

Make sure you have a working installation of `CMake` (at least version 3.8) as
well as a working C++ 14 compiler. Both GCC and MSVC toolchains are supported.

### CLI/REPL

The project is compiled just like any CMake project. Just create a dedicated
`build` directory and configure the project before building it:

```sh
mkdir -p build
cd build
cmake ..
cmake --build .
```

For `Release` builds:

```sh
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

The built binary should be found under the `cli/` folder in the build directory.

### Web Playground

You can use [Emscripten] to build the WASM module containing bindings to the
NanoTekSpice engine. Using the `emcmake` tool makes this very easy.

```sh
mkdir -p build_wasm
cd build_wasm
emcmake cmake ..
cmake --build .
```

[Epitech]: https://epitech.eu
[Emscripten]: https://emscripten.org/docs/getting_started/downloads.html
