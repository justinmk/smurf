const util = require('util');
const fs = require('fs');
var wasm = fs.readFileSync('./main.wasm');
const env = {
    memoryBase: 0,
    tableBase: 0,
    memory: new WebAssembly.Memory({
      initial: 256
    }),
    table: new WebAssembly.Table({
      initial: 0,
      element: 'anyfunc'
    })
  }

var typedArray = new Uint8Array(wasm);

WebAssembly.instantiate(typedArray, {
  env: env
}).then(result => {
  console.log(util.inspect(result, true, 0));
  console.log(result.instance.exports._add(9, 9));
}).catch(e => {
  // error caught
  console.log(e);
});
