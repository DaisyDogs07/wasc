(() => {
  const memory = new WebAssembly.Memory({
    initial: Math.ceil((64 * 1024 * 1024) / (64 * 1024))
  });
  let ex;
  let wasmMalloc;
  let wasmRealloc;

  function malloc(size) {
    try {
      return wasmMalloc(size);
    } catch {
      return 0;
    }
  }

  function realloc(ptr, size) {
    try {
      return wasmRealloc(ptr, size);
    } catch {
      return 0;
    }
  }

  function makeString(str) {
    const ptr = malloc(str.length + 1);
    for (let i = 0; i != str.length; ++i)
      ex.writeUint8(ptr + i, str.charCodeAt(i));
    ex.writeUint8(ptr + str.length, 0);
    return ptr;
  }

  function getString(addr) {
    let str = '';
    let i = 0;
    while (true) {
      const c = ex.readUint8(addr + i++);
      if (c == 0)
        break;
      str += String.fromCharCode(c);
    }
    return str;
  }

  if (typeof window === 'undefined') {
    const fs = require('fs');
    ex = {
      ...new WebAssembly.Instance(
        new WebAssembly.Module(fs.readFileSync('utils.wasm')),
        {
          env: {
            malloc,
            memory
          }
        }
      ).exports
    };
    module.exports = ex;
    wasmMalloc = ex.wasmMalloc;
    wasmRealloc = ex.wasmRealloc;
    delete ex.wasmMalloc;
    delete ex.wasmRealloc;
    Object.assign(ex, {
      malloc,
      realloc,
      makeString,
      getString
    });
  } else {
    ex = new Promise((res, rej) => {
      fetch('utils.wasm')
        .then(r => r.arrayBuffer())
        .then(buf => {
          res({
            ...new WebAssembly.Instance(
              new WebAssembly.Module(buf),
              {
                env: {
                  malloc,
                  memory
                }
              }
            ).exports
          });
        })
        .catch(rej);
    });
    Object.assign(window, {
      wasc: ex
    });
    ex.then(res => {
      ex = res;
      Object.assign(window, {
        wasc: ex
      });
      wasmMalloc = ex.wasmMalloc;
      wasmRealloc = ex.wasmRealloc;
      delete ex.wasmMalloc;
      delete ex.wasmRealloc;
      Object.assign(ex, {
        malloc,
        realloc,
        makeString,
        getString
      });
    });
  }
})();