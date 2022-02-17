'use strict';
const util = require('util');
const fs = require('fs');
// Go WASM bootstrap
// XXX: puts "Go" in global scope.
const goWasm = require('./wasm_exec');

const { readFile } = require('fs/promises');
const { join } = require('path');

async function loadWasm() {
  const go = new Go()
  // Pass environment to Go WASM.
  go.env = Object.assign({ TMPDIR: require("os").tmpdir() }, process.env);
  const importObject = {
    ...go.importObject,
  };
  // var typedArray = new Uint8Array(wasm);
  // TODO: WebAssembly.instantiateStreaming not available in node yet?
  const wasm = await WebAssembly.compile(
    await readFile(join(__dirname, './main.wasm'))
  );
  const instance = await WebAssembly.instantiate(wasm, importObject);
  go.run(instance)
  // console.log(global.foo.test1())
  // console.log(global.foo.test2())
}

(async () => {
  await loadWasm()
})();

