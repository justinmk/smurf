# WASM as a shared library

> An experience report on using WASM as a cross-platform code sharing solution.

## background

To share code across platforms in a portable library, the story up to now has been C libs (`.so`, `.dylib`, `.dll).
This is approximately because (1) most sytems have a C runtime and (2) most programming languages have interop with the C ABI ("FFI").
But C as the common substrate isn't great because (1) people don't want to write C, (2) building and distributing the C libs takes finesse, (3) marshalling to/from C to/from the host language is awkward and bespoke.
Common workaround is various forms of transpilation: Cordova, macros

Because operating systems failed at their job, "the web" emerged as the
actual lowest common denominator and most cross-platform viable runtime.
Unlike C libs, the web has sandboxing and a delivery model with URIs.
Blame the OS vendors.

WebAssembly (WASM) looks like a good answer for a more secure and reliable way to share code in the web _plus_ traditional native applications.


## summary

* tried "fancy" WASM runtimes.
* "vanilla" WASM works better than expected.
* authored some AWS logic in Go
* works in browser, nodejs
* TODO: vscode, jetbrains, visualstudio

## "fancy" WASM runtimes

1. wasmer
    1. X extra layer/ecosystem, immature tooling
2. [AssemblyScript](https://www.assemblyscript.org/)
    1. X extra layer, immature, no gain vs e.g. Go/Rust/etc.

## vanilla WASM (+ Go)

some platforms such as Go "just work".

* go: fast, easy. supports WASM out of the box.
* vs...
    * kotlin: requires "kotlin native" + limitations
    * rust: exported functions are automatically available?

## WASM (+ Go): state of the art

### good

* super fast ramp up (developer setup, dev-test cycle)
* AWS SDK for Go appears to "just work" in WASM
* Go features like goroutines, `net/http` "just work" in WASM

## WASM (+ Go): state of the art

### limitations

* only supports primitive data types (int, string, maps, …)
    * non-primitives must be serialized
        * BUT, we already do this with "native" clients...
        * comparable to RPC, FFI...
* no shared closures
    * FUTURE: [WASM proposal: function references](https://github.com/WebAssembly/function-references/blob/master/proposals/function-references/Overview.md)
* no shared types (like Microsoft COM)
    * FUTURE: [WASM proposal: interface types](https://github.com/WebAssembly/interface-types/blob/main/proposals/interface-types/Explainer.md)
    * FUTURE: [WASM proposal: type imports/exports](https://github.com/WebAssembly/proposal-type-imports)
* debug WASM via printf or raw assembly
    * FUTURE: debug wasm in Chrome: https://developer.chrome.com/blog/wasm-debugging-2020/
* `js.Global()` assumes a JS engine is available. (WebAssembly does not require a JavaScript VM by design).
    * For non-NodeJS platforms (Java, .NET, …) we need WASI and probably "type imports" (see above).


## WASM (+ Go): state of the art

* `main.wasm` = 10M
* to export a function: `js.Global().Set("myFunc", fn)`
* WASM [works in vscode](https://github.com/microsoft/vscode/issues/65559#issuecomment-751439479)
* for network (`net/http` in Go), need `fetch`
    * shipped with all browsers
    * shipped with Node since 17.5 (`node --experimental-fetch`)

## ramp up / quick start

We need a WASM library and some sort of application or script that loads it.

1. install Go
2. install [aws-sdk-go-v2](https://github.com/aws/aws-sdk-go-v2)
3. author some library code (`main.go`)
3. author some application code
    * Example: `node_main.js` is a Node script loads and invokes the WASM library.
4. build: `GOOS=js GOARCH=wasm go build -o main.wasm`
5. run the code
    * Example: `node --experimental-fetch --experimental-wasi-unstable-preview1 node_main.js`
        * nodejs doesn't ship with `fetch` yet so we need `--experimental-fetch`

## reference
* https://github.com/golang/go/wiki/WebAssembly#getting-started
* https://github.com/stdiopt/gowasm-experiments
* https://github.com/golang/go/wiki/WebAssembly#further-examples
* WASI: https://github.com/bytecodealliance/wasmtime/blob/main/docs/WASI-tutorial.md
* nodejs WASI: https://nodejs.org/api/wasi.html

## bridge

* export a map of functions to JS: `js.Global().Set("foo", exportMap)`

## project structure

* `wasm_exec.js` should match the Go version.
    * it comes from `"$(go env GOROOT)/misc/wasm/wasm_exec.js"`

## conclusion

* wasm + go is viable for a shared library.
    * may need to wait on WASI for use of network/filesystem in non-NodeJS platforms (Java, .NET).
* compares favorably to RPC and FFI on most dimensions.

## next steps

* in nodejs need to import `fetch` or use `node --experimental-fetch` (Node 17.5)
* test vscode
* test Kotlin/JetBrains.
    * Does `wasm_exec.js` need to be reimplemented for Kotlin?
        * Alternative: [WASI](https://github.com/bytecodealliance/wasmtime/blob/main/docs/WASI-tutorial.md)), need [KT-36172](https://youtrack.jetbrains.com/issue/KT-36172)
* test C#/VisualStudio.
    * Does `wasm_exec.js` need to be reimplemented for .NET? (Alternative: wait for [WASI](https://github.com/bytecodealliance/wasmtime/blob/main/docs/WASI-tutorial.md))
