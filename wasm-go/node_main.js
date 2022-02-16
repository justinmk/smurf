const util = require('util');
const fs = require('fs');
// Go WASM bootstrap
// XXX: puts "Go" in global scope.
const goWasm = require('./wasm_exec');

// patch in fetch for nodejs (will ship with future versions of node)
global.fetch = require('node-fetch')
// global.Headers = fetch.Headers;
console.log(fetch)
global.Headers = fetch.Headers
new fetch.Headers({'content-type': 'application/json'})


// var wasm = fs.readFileSync('./main.wasm');
// const env = {
//     memoryBase: 0,
//     tableBase: 0,
//     memory: new WebAssembly.Memory({
//       initial: 256
//     }),
//     table: new WebAssembly.Table({
//       initial: 0,
//       element: 'anyfunc'
//     })
//   }
// var typedArray = new Uint8Array(wasm);
// WebAssembly.instantiate(typedArray, {
//   env: env
// }).then(result => {
//   console.log(util.inspect(result, true, 0));
//   console.log(result.instance.exports._add(9, 9));
//   // exported Test() function from main.go
//   // wasm.Test(7234)
// }).catch(e => {
//   // error caught
//   console.log(e);
// });

const go = new Go()
const goWasmFile = './main.wasm'
// TODO: WebAssembly.instantiateStreaming not available in node yet?
// var typedArray = new Uint8Array(wasm);
WebAssembly.instantiate(
  fs.readFileSync(goWasmFile),
  go.importObject
).then(result => {
  go.run(result.instance)
  console.log(global.foo.test1())
  console.log(global.foo.test2())
}).catch(e => {
  console.error(`failed to load ${goWasmFile}`, e);
});
