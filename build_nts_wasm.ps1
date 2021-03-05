$jobs = (Get-WmiObject -class Win32_ComputerSystem).numberoflogicalprocessors

# configure
docker run --rm -itw /code/build_wasm -v "$(pwd):/code" 'emscripten/emsdk' `
    emcmake cmake .. `
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/code/bonus/web_playground/public

# build
docker run --rm -itw /code/build_wasm -v "$(pwd):/code" 'emscripten/emsdk' `
    cmake --build . --target nts -- "-j$jobs"
