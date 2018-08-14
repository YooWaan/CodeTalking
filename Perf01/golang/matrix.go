package main

import (
	"fmt"
	"sync"
)

type Answer struct {
	Size int
	Row  int
	Col  int
}

func mul(l, r [][]int) [][]int {
	sz := len(l)
	ans := make([][]int, sz)
	for i := 0; i < sz; i++ {
		row := make([]int, sz)
		for n := 0; n < sz; n++ {
			for m := 0; m < sz; m++ {
				row[n] += l[i][m] * r[m][n]
			}
		}
		ans[i] = row
	}
	return ans
}

func left(sz int) [][]int {
	ret := make([][]int, sz)
	for i := 1; i < sz+1; i++ {
		row := make([]int, sz)
		for n := 1; n < sz+1; n++ {
			row[n-1] = i
		}
		ret[i-1] = row
	}
	return ret
}

func right(sz int) [][]int {
	ret := make([][]int, sz)
	for i := 1; i < sz+1; i++ {
		row := make([]int, sz)
		for n := 1; n < sz+1; n++ {
			row[n-1] = n
		}
		ret[i-1] = row
	}
	return ret
}

func show(m [][]int) {
	for _, r := range m {
		fmt.Printf("%v\n", r)
	}
}

func calc(done <-chan struct{}, sz int) []Answer {
	ch := make(chan Answer)
	var wg sync.WaitGroup
	as := make([]Answer, 0)

	go func() {
		defer close(ch)
		for i := 1; i < sz; i++ {
			wg.Add(1)
			go func(n int) {
				v := mul(left(n), right(n))
				ans := Answer{n, len(v), len(v[0])}
				select {
				case ch <- ans:
				case <-done:
				}
				wg.Done()
			}(i)
		}
		wg.Wait()
	}()

	// main thread
	for a := range ch {
		//println(fmt.Sprintf("wait >%v", a))
		as = append(as, a)
	}

	return as
}

func run(size int) int {
	done := make(chan struct{})
	defer close(done)
	as := calc(done, size+1)
	return len(as)
}

func main() {
	cnt := run(10)
	fmt.Println("Count:", cnt)
}
