#!/bin/sh

if ! command -v clang >/dev/null || ! command -v wasm-ld >/dev/null
then
  echo "Clang with WebAssembly support not found"
  exit 1
fi

for file in ./*.c; do
  clang -ffreestanding -nostdlib -fno-inline -Os -target wasm32 -c $file
done

wasm-ld --no-entry --export-dynamic --import-memory --strip-all -o utils.wasm *.o
rm *.o