// go-wasm vs...
//    kotlin: requires "kotlin native" + limitations
//
// notes
//    main.wasm = 12M
//    goroutines work?!
//    net/http works!
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
//    node wasm_exec.js main.wasm
//
// https://github.com/golang/go/wiki/WebAssembly#configuring-fetch-options-while-using-nethttp
//
// debug wasm in Chrome: https://developer.chrome.com/blog/wasm-debugging-2020/
//
// TODO:
//    import main.wasm (import its types, call its functions) from host?
//      import * as M from './add.wasm';
//    wasm_exec.js probably is only needed for browser (or entrypoint for nodejs)
//      https://nodejs.dev/learn/nodejs-with-webassembly
//      call WebAssembly.instantiate from nodejs
//    optimize
//      smaller size via tinygo? https://tinygo.org/docs/reference/lang-support/stdlib/
//
//

package main

import (
	"context"
	"flag"
	"fmt"
	"os"
	"time"

	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/aws/awserr"
	"github.com/aws/aws-sdk-go/aws/request"
	"github.com/aws/aws-sdk-go/aws/session"
	"github.com/aws/aws-sdk-go/service/s3"
)




// Uploads a file to S3 given a bucket and object key. Also takes a duration
// value to terminate the update if it doesn't complete within that time.
//
// The AWS Region needs to be provided in the AWS shared config or on the
// environment variable as `AWS_REGION`. Credentials also must be provided
// Will default to shared config file, but can load from environment if provided.
//
// Usage:
//   # Upload myfile.txt to myBucket/myKey. Must complete within 10 minutes or will fail
//   go run withContext.go -b mybucket -k myKey -d 10m < myfile.txt
func awsstuff() {
	var bucket, key string
	var timeout time.Duration

	flag.StringVar(&bucket, "b", "", "Bucket name.")
	flag.StringVar(&key, "k", "", "Object key name.")
	flag.DurationVar(&timeout, "d", 0, "Upload timeout.")
	flag.Parse()

	// All clients require a Session. The Session provides the client with
      // shared configuration such as region, endpoint, and credentials. A
      // Session should be shared where possible to take advantage of
      // configuration and credential caching. See the session package for
      // more information.
	sess := session.Must(session.NewSession())

      // Create a new instance of the service's client with a Session.
      // Optional aws.Config values can also be provided as variadic arguments
      // to the New function. This option allows you to provide service
      // specific configuration.
	svc := s3.New(sess)

	// Create a context with a timeout that will abort the upload if it takes
	// more than the passed in timeout.
	ctx := context.Background()
	var cancelFn func()
	if timeout > 0 {
		ctx, cancelFn = context.WithTimeout(ctx, timeout)
	}
	// Ensure the context is canceled to prevent leaking.
	// See context package for more information, https://golang.org/pkg/context/
      if cancelFn != nil {
		defer cancelFn()
      }

	// Uploads the object to S3. The Context will interrupt the request if the
	// timeout expires.
	_, err := svc.PutObjectWithContext(ctx, &s3.PutObjectInput{
		Bucket: aws.String(bucket),
		Key:    aws.String(key),
		Body:   os.Stdin,
	})
	if err != nil {
		if aerr, ok := err.(awserr.Error); ok && aerr.Code() == request.CanceledErrorCode {
			// If the SDK can determine the request or retry delay was canceled
			// by a context the CanceledErrorCode error code will be returned.
			fmt.Fprintf(os.Stderr, "upload canceled due to timeout, %v\n", err)
		} else {
			fmt.Fprintf(os.Stderr, "failed to upload object, %v\n", err)
		}
		os.Exit(1)
	}

	fmt.Printf("successfully uploaded file to %s/%s\n", bucket, key)
}

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
        awsstuff()
        go test(1)
        go test(2)
        go test(3)
        waittt()
}

