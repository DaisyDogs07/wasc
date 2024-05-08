#!/bin/sh

if ! command -v clang >/dev/null || ! command -v wasm-ld >/dev/null
then
  echo "Clang with WebAssembly support not found"
  exit 1
fi

for file in ./*.c; do
  if ! clang -ffreestanding -nostdlib -fno-inline -O2 -target wasm32 -c $file
  then
    rm *.o
    exit 1
  fi
done

if ! wasm-ld --no-entry --export-dynamic --import-memory --strip-all -o utils.wasm *.o
then
  rm *.o
  exit 1
fi
rm *.o