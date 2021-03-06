$jobs = (Get-WmiObject -class Win32_ComputerSystem).numberoflogicalprocessors

# configure
docker run --rm -itw /code/build_wasm -v "$(pwd):/code" 'emscripten/emsdk' `
    emcmake cmake .. `
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/code/build_wasm

# build
docker run --rm -itw /code/build_wasm -v "$(pwd):/code" 'emscripten/emsdk' `
    cmake --build . --target nts -- "-j$jobs"

# copy the files
cp -Force .\build_wasm\nts.wasm .\bonus\web_playground\public\nts.wasm
cp -Force .\build_wasm\nts.js .\bonus\web_playground\src\nts.js
