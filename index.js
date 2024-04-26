(() => {
  const memory = new WebAssembly.Memory({
    initial: Math.ceil((64 * 1024 * 1024) / (64 * 1024))
  });
  let ex;

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
            memory
          }
        }
      ).exports
    };
    module.exports = ex;
    Object.assign(ex, {
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
      Object.assign(ex, {
        makeString,
        getString
      });
    });
  }
})();