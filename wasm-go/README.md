WASM as a shared library
========================

- goal: reusable common library that can be shared with all Toolkits (VSCode, JetBrains, Visual Studio, …)

summary
------------

- tried "fancy" WASM runtimes.
- "vanilla" WASM works better than expected.
- authored some AWS logic in Go
- works in browser, nodejs
- TODO: vscode, jetbrains, visualstudio

"fancy" WASM runtimes
------------
1. wasmer
    - X extra layer/ecosystem, immature tooling
2. [AssemblyScript](https://www.assemblyscript.org/)
    - X extra layer, immature, no gain vs e.g. Go/Rust/etc.

vanilla WASM (+ Go)
------------
some platforms such as Go "just work".

- go: fast, easy. supports WASM out of the box.
- vs...
   - kotlin: requires "kotlin native" + limitations
   - rust: exported functions are automatically available?

WASM (+ Go): state of the art
------------

### good
- super fast ramp up (developer setup, dev-test cycle)
- AWS SDK for Go appears to "just work" in WASM
- Go features like goroutines, `net/http` "just work" in WASM

WASM (+ Go): state of the art
------------

### limitations
- only supports primitive data types (int, string, maps, …)
    - non-primitives must be serialized
        - BUT, we already do this with "native" clients...
        - comparable to RPC, FFI...
- no shared closures
    - FUTURE: [WASM proposal: function references](https://github.com/WebAssembly/function-references/blob/master/proposals/function-references/Overview.md)
- no shared types (like Microsoft COM)
    - FUTURE: [WASM proposal: interface types](https://github.com/WebAssembly/interface-types/blob/main/proposals/interface-types/Explainer.md)
    - FUTURE: [WASM proposal: type imports/exports](https://github.com/WebAssembly/proposal-type-imports)
- debug WASM via printf or raw assembly
    - FUTURE: debug wasm in Chrome: https://developer.chrome.com/blog/wasm-debugging-2020/


WASM (+ Go): state of the art
------------

- `main.wasm` = 10M
- to export a function: `js.Global().Set("myFunc", fn)`
- WASM [works in vscode](https://github.com/microsoft/vscode/issues/65559#issuecomment-751439479)
- for network (`net/http` in Go), need `fetch`
    - shipped with all browsers
    - shipped with Node since 17.5 (`node --experimental-fetch`)

ramp up / quick start
---------------------

2. install Go
3. install aws-sdk-go
4. author some code (`main.go`)
5. build
    - `GOOS=js GOARCH=wasm go build -o main.wasm`

reference
---------
- https://github.com/golang/go/wiki/WebAssembly#getting-started
- https://github.com/stdiopt/gowasm-experiments
- https://github.com/golang/go/wiki/WebAssembly#further-examples


bridge
------

export a map of functions to JS:

    js.Global().Set("foo", exportMap)


project structure
-----------------
- `wasm_exec.js` should match the Go version.
    - it comes from `"$(go env GOROOT)/misc/wasm/wasm_exec.js"`

conclusion
------------
- wasm + go is viable for a shared library.
- compares favorably to RPC and FFI on most (all?) dimensions.

next steps
----------
- in nodejs need to import `fetch` or use `node --experimental-fetch` (Node 17.5)
- test Kotlin/JetBrains
- test C#/VisualStudio
