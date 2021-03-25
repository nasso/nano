#!/bin/bash

set -e

echo "<-------------------------->"
echo "<-- Building WASM module -->"
echo "<-------------------------->"
(
  APP_DIR=$(pwd)
  BUILD_DIR=/tmp/libnts/build

  rm -rf $BUILD_DIR
  mkdir -p $BUILD_DIR
  cd $BUILD_DIR

  # configure
  emcmake cmake "$APP_DIR/libnts" -G "Unix Makefiles" \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$BUILD_DIR

  # build
  cmake --build . --target nts -- "-j$(nproc)"

  # copy the files
  mkdir -p "$APP_DIR/public/build"
  cp -f ./nts.wasm "$APP_DIR/public/build/nts.wasm"
  cp -f ./nts.js "$APP_DIR/src/nts.js"
)
echo "<------------------------->"
echo "<-- Built successfully! -->"
echo "<------------------------->"
