// go-wasm vs...
//    kotlin: requires "kotlin native" + limitations
//
// getting started
//    https://github.com/golang/go/wiki/WebAssembly#getting-started
//
// build:
//    GOOS=js GOARCH=wasm go build -o main.wasm
//
// run in browser:
//    go get -u github.com/shurcooL/goexec
//    ~/go/bin/goexec 'http.ListenAndServe(`:8080`, http.FileServer(http.Dir(`.`)))'
//
// run in nodejs:
//    https://github.com/golang/go/wiki/WebAssembly#executing-webassembly-with-nodejs
//
// https://github.com/golang/go/wiki/WebAssembly#configuring-fetch-options-while-using-nethttp
//
// debug wasm in Chrome: https://developer.chrome.com/blog/wasm-debugging-2020/
//
//
//

package main

import "fmt"
import "time"

func test(i int) {
	fmt.Printf("Hello, WebAssembly! %v\n", 41 + i)
}

func waittt() {
    channel := make(chan int)
    go func() {
        time.Sleep(3*time.Second)
        channel <- 1 // Sending something to the channel to let the main thread continue
        channel <- 2
    }()

    for {
        fmt.Println("../");
        <-channel // Waiting for something to come from the channel
    }
}

func main() {
	fmt.Printf("Hello, WebAssembly! %v\n", 41 + 1)
        go test(1)
        go test(2)
        go test(3)
        waittt()
}
