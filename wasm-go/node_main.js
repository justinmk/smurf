// 'use strict';
const util = require('util');
const fs = require('fs');
// Go WASM bootstrap
// XXX: puts "Go" in global scope.
const goWasm = require('./wasm_exec');

const { readFile } = require('fs/promises');
const { WASI } = require('wasi');
const { argv, env } = require('process');
const { join } = require('path');

async function loadWasm() {
  const go = new Go()
  const wasi = new WASI({
    args: argv,
    env,
    preopens: {
      '/': '/',
      '/Users/jmkeyes': '/Users/jmkeyes',
    }
  });

  // Some WASI binaries require:
  //   const importObject = { wasi_unstable: wasi.wasiImport };
  const importObject = {
    ...go.importObject,
    wasi_snapshot_preview1: wasi.wasiImport,
    wasi_unstable: wasi.wasiImport,
  };

  // var typedArray = new Uint8Array(wasm);
  // TODO: WebAssembly.instantiateStreaming not available in node yet?
  const wasm = await WebAssembly.compile(
    await readFile(join(__dirname, './main.wasm'))
  );
  const instance = await WebAssembly.instantiate(wasm, importObject);
  wasi.start(instance);
  // go.run(instance)
  // console.log(global.foo.test1())
  // console.log(global.foo.test2())
}

(async () => {
  await loadWasm()
})();

