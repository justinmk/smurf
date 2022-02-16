// notes
//    main.wasm = 12M
//    goroutines work!
//    net/http works!
//    to export a function: js.Global().Set("myFunc", fn)
//    wasm in vscode extension: https://github.com/microsoft/vscode/issues/65559#issuecomment-751439479
//    currently required serialization to send/receive data across the WASM barrier
//	but this is not different than RPC... and FFI requires marshalling
//	in the future, closures and typed data will be supported (TODO: reference wasm proposals)
//
// getting started
//    https://github.com/golang/go/wiki/WebAssembly#getting-started
//    install aws-sdk-go
//
// build:
//    GOOS=js GOARCH=wasm go build -o main.wasm
//
// run in browser:
//    go get -u github.com/shurcooL/goexec
//    ~/go/bin/goexec 'http.ListenAndServe(`:8080`, http.FileServer(http.Dir(`.`)))'
//
// run in nodejs:
//    node node_main.js
//
// run in vscode extension:
//    import 'wasm_exec'
//
// https://github.com/golang/go/wiki/WebAssembly#configuring-fetch-options-while-using-nethttp
//
// debug wasm in Chrome: https://developer.chrome.com/blog/wasm-debugging-2020/
//
// TODO:
//    why is nodejs much slower than Chrome?
//    import main.wasm (import its types, call its functions) from host?
//      import * as M from './add.wasm';
//    wasm_exec.js only needed for browser/nodejs? or also c#, kotlin?
//      https://nodejs.dev/learn/nodejs-with-webassembly
//    optimize
//      smaller size via tinygo? https://tinygo.org/docs/reference/lang-support/stdlib/
//

package main

import (
	"syscall/js" // wasm. https://medium.com/swlh/getting-started-with-webassembly-and-go-by-building-an-image-to-ascii-converter-dea10bdf71f6

	"context"
	"log"
	// "flag"
	// "os"

	"fmt"
	"time"
	"encoding/json"

	// "github.com/aws/aws-sdk-go-v2/aws"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/s3"

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
// func awsstuff() error {
// 	var bucket, key string
// 	var timeout time.Duration

// 	flag.StringVar(&bucket, "b", "", "Bucket name.")
// 	flag.StringVar(&key, "k", "", "Object key name.")
// 	flag.DurationVar(&timeout, "d", 0, "Upload timeout.")
// 	flag.Parse()

// 	// All clients require a Session. The Session provides the client with
// 	// shared configuration such as region, endpoint, and credentials. A
// 	// Session should be shared where possible to take advantage of
// 	// configuration and credential caching. See the session package for
// 	// more information.
// 	sess := session.Must(session.NewSession())

// 	// Create a new instance of the service's client with a Session.
// 	// Optional aws.Config values can also be provided as variadic arguments
// 	// to the New function. This option allows you to provide service
// 	// specific configuration.
// 	svc := s3.New(sess)

// 	// Create a context with a timeout that will abort the upload if it takes
// 	// more than the passed in timeout.
// 	ctx := context.Background()
// 	var cancelFn func()
// 	if timeout > 0 {
// 		ctx, cancelFn = context.WithTimeout(ctx, timeout)
// 	}
// 	// Ensure the context is canceled to prevent leaking.
// 	// See context package for more information, https://golang.org/pkg/context/
// 	if cancelFn != nil {
// 		defer cancelFn()
// 	}

// 	// Uploads the object to S3. The Context will interrupt the request if the
// 	// timeout expires.
// 	_, err := svc.PutObjectWithContext(ctx, &s3.PutObjectInput{
// 		Bucket: aws.String(bucket),
// 		Key:    aws.String(key),
// 		Body:   os.Stdin,
// 	})
// 	if err != nil {
// 		if aerr, ok := err.(awserr.Error); ok && aerr.Code() == request.CanceledErrorCode {
// 			// If the SDK can determine the request or retry delay was canceled
// 			// by a context the CanceledErrorCode error code will be returned.
// 			fmt.Fprintf(os.Stderr, "upload canceled due to timeout, %v\n", err)
// 		} else {
// 			fmt.Fprintf(os.Stderr, "failed to upload object, %v\n", err)
// 		}
// 		return err
// 	}

// 	fmt.Printf("successfully uploaded file to %s/%s\n", bucket, key)
// 	return nil
// }

func Test(i int) {
	fmt.Printf("Hello, WebAssembly! %v\n", 41 + i)
}

func waittt() {
    channel := make(chan int)
    go func() {
        time.Sleep(300*time.Second)
        channel <- 1 // Sending something to the channel to let the main thread continue
        channel <- 2
    }()

    for {
        fmt.Println("../");
        <-channel // Waiting for something to come from the channel
    }
}

func listbuckets() string {
	// creds := credentials.NewStaticCredentials("AKID", "SECRET", "SESSION")
	// creds := credentials.NewStaticCredentials()

	// Load the Shared AWS Configuration (~/.aws/config)
	cfg, err := config.LoadDefaultConfig(context.TODO())
	if err != nil {
		log.Fatal(err)
	}
	// Create an Amazon S3 service client
	client := s3.NewFromConfig(cfg)

	// Get the first page of results for ListObjectsV2 for a bucket
	// output, err := client.ListObjectsV2(context.TODO(), &s3.ListObjectsV2Input{
	// 	Bucket: aws.String("my-bucket"),
	// })

	output, err := client.ListBuckets(context.TODO(), &s3.ListBucketsInput{})

	if err != nil {
		log.Fatal(err)
	}

	log.Println("first page results:")
	for _, bucket := range output.Buckets {
		log.Println(*bucket.Name + ": " + bucket.CreationDate.Format("2006-01-02 15:04:05 Monday"))

	}

	r, err2 := json.Marshal(cfg)
	if err2 != nil {
		return ""
	}
	return string(r)
}

// https://stackoverflow.com/q/55536425
func main() {
	c := make(chan bool)
        // js.Global().Set("Test", js.FuncOf(Test))
        // func(js.Value, []js.Value) interface {}
	exportMap := map[string]interface{} {
		"test1": js.FuncOf(func(this js.Value, args []js.Value) interface{} {
			return "test 1 result"
		}),
		"test2": js.FuncOf(func(this js.Value, args []js.Value) interface{} {
			// https://pkg.go.dev/syscall/js#FuncOf
			// > if one wrapped function blocks, JavaScript's event
			// > loop is blocked until that function returns.
			// > Hence, calling any async JavaScript API, which
			// > requires the event loop, like fetch (http.Client),
			// > will cause an immediate deadlock. Therefore
			// > a blocking function should explicitly start a new goroutine.
			go listbuckets()
			return ""
		}),
	}
        js.Global().Set("foo", exportMap)

	fmt.Printf("Hello, WebAssembly! %v\n", 41 + 1)
        // awsstuff()
        go Test(1)
        go Test(2)
        go Test(3)
        waittt()
	listbuckets()
	// Do not exit, wait forever (act as a library).
	<-c
}

