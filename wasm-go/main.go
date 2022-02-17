// build:
//    GOOS=js GOARCH=wasm go build -o main.wasm
//
// run in browser:
//    go get -u github.com/shurcooL/goexec
//    ~/go/bin/goexec 'http.ListenAndServe(`:8080`, http.FileServer(http.Dir(`.`)))'
//
// run in nodejs:
//    # fetch available since node 17.5: https://nodejs.org/en/blog/release/v17.5.0/
//    node --experimental-fetch --experimental-wasi-unstable-preview1 node_main.js
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
	"io/ioutil"
	"log"

	// "flag"
	// "os"

	"encoding/json"
	"fmt"

	// Overview: https://aws.github.io/aws-sdk-go-v2/docs/migrating/
	// "github.com/aws/aws-sdk-go-v2/aws"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/s3"

	"net/http"
	// awshttp "github.com/aws/aws-sdk-go-v2/aws/transport/http"
	// "github.com/aws/aws-sdk-go-v2/aws/external"
)

type s struct {
	cl http.Client
}

func (s s) Do(r *http.Request) (*http.Response, error) {
	// "no-cors" needed in browser (not nodejs) for "localhost:8080".
	// https://github.com/golang/go/wiki/WebAssembly#configuring-fetch-options-while-using-nethttp
	r.Header.Add("js.fetch:mode", "no-cors")
	// r.Header.Add("js.fetch:credentials", "include")
	// r.Header.Add("js.fetch:redirect", "follow")
	return s.cl.Do(r)
}

func listDir() {
	files, err := ioutil.ReadDir("./")
	if err != nil {
		log.Fatal(err)
	}

	for _, f := range files {
		fmt.Println(f.Name())
	}
}

func listbuckets() string {
	// httpClient := awshttp.NewBuildableClient().WithTransportOptions(func(tr *http.Transport) {
	// 	tr.ExpectContinueTimeout = 0
	// 	tr.MaxIdleConns = 10
	// })

	// Load the Shared AWS Configuration (~/.aws/config)
	cfg, err := config.LoadDefaultConfig(
		context.Background(),
		// config.WithCredentialsProvider(credentials.NewStaticCredentialsProvider(credentials.NewStaticCredentials(…))),
		// config.WithSharedConfigProfile("default"),
		// config.WithRegion("us-west-2"),
		// https://stackoverflow.com/a/68955337/152142
		config.WithHTTPClient(s{http.Client{}}),
		// config.WithEndpointResolver(aws.EndpointResolverFunc(func(service, region string) (aws.Endpoint, error) {
		// 	return aws.Endpoint{
		// 		PartitionID:       "aws",
		// 		URL:               "http://localhost:4566",
		// 		SigningRegion:     "eu-west-1",
		// 		HostnameImmutable: true,
		// 		// Source:        aws.EndpointSourceCustom,
		// 	}, nil
		// })),
	)

	creds, credsErr := cfg.Credentials.Retrieve(context.Background())
	if credsErr != nil {
		log.Fatal(err)
	}
	fmt.Printf("AWS credentials:\n    region=%v\n    accesskey=%v\n    error: %v\n", cfg.Region, creds.AccessKeyID, credsErr)

	// Create an Amazon S3 service client
	client := s3.NewFromConfig(cfg)
	output, err := client.ListBuckets(context.Background(), &s3.ListBucketsInput{})
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("S3 buckets:\n")
	i := 0
	for _, bucket := range output.Buckets {
		if i > 10 {
			break
		}
		fmt.Printf("    %v: %v\n", *bucket.Name, bucket.CreationDate.Format("2006-01-02 15:04:05 Monday"))
		i++
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
	exportMap := map[string]interface{}{
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

			// go listbuckets()
			return ""
		}),
	}
	js.Global().Set("foo", exportMap)

	fmt.Printf("Hello, WebAssembly! %v\n", 41+1)
	listDir()
	listbuckets()
	// Do not exit, wait forever (act as a library).
	<-c
}
