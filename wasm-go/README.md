WASM experience report
======================

summary
------------
- compiled a Go library 

tried
------------
1. wasmer
    - X extra layer/ecosystem, immature tooling
2. AssemblyScript
    - X extra layer, immature, no gain vs e.g. Go/Rust/etc.
3. vanilla WASM
    - some platforms such as Go "just work"

vanilla WASM: Go + WASM
------------
- go: fast, easy. supports WASM out of the box.
- vs...
   - kotlin: requires "kotlin native" + limitations
   - rust: exported functions are automatically available?

Go + WASM: state of the art
------------

### good
- super fast ramp up (developer setup, dev-test cycle)
- AWS SDK for Go appears to "just work" in WASM
- Go features like goroutines "just work" in WASM

### bad
- data passed to host as JS objects; typed hosts will likely want to map to formal types
    - BUT, we already do this with even native clients!
- shared types, typed parameters (like Microsoft COM)
    - FUTURE: proposed WASM feature
- closures
    - FUTURE: proposed WASM feature


bridge
------

export a map of functions to JS:

    js.Global().Set("foo", exportMap)


conclusion
------------
wasm + go is viable for a shared library that can be loaded in the browser sandbox, nodejs, kotlin, C#, and of course any dynamic language that has a wasm runtime.
compares favorably to RPC and FFI on most (all?) dimensions.
missing: typed marshaling, closures (ergonomics)

xxxxxxxxx
-----------

- https://github.com/stdiopt/gowasm-experiments
- https://github.com/golang/go/wiki/WebAssembly#further-examples
