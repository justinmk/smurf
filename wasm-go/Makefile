all: main.wasm

run: | all
	node --experimental-fetch \
		--experimental-wasi-unstable-preview1 \
		node_main.js

main.wasm: main.go
	GOOS=js GOARCH=wasm go build -o main.wasm


clean:
	rm -f main.wasm

.PHONY: all run clean

