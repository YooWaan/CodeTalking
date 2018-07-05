package main

import (
	"flag"
	"fmt"

	"github.com/YooWaan/CodeTalking/Perf01/wc"
)

func sq() []wc.FileCount {
	results := make([]wc.FileCount, 0)
	for _, fnm := range flag.Args() {
		if c, err := wc.Run(fnm); err != nil {
			fmt.Errorf("%s : [%v]\n", fnm, err)
			continue
		} else {
			results = append(results, c)
		}
	}
	return results
}

func pl() []wc.FileCount {
	results := make([]wc.FileCount, 0)
	for _, fnm := range flag.Args() {
		cnt := wc.RunParallel(fnm)
		results = append(results, cnt)
	}
	return results
}


func main() {
	flag.Parse()

	//results := sq()
	results := pl()

	fmt.Printf("re [%d]\n", len(results))
	for _, count := range results {
		fmt.Printf("%7d %7d %7d %s\n", count.Lines, count.Words, count.Bytes, count.FileName)
	}
}
