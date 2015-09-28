package main

import ( "fmt"; "time" )

func timestamp() int64 {
	return time.Now().UnixNano() / int64(time.Millisecond)
}

func fib(n int64) int64 {
	if n <= 1 {
		return n
	}
	return fib(n-1) + fib(n-2)
}

func calc(i int, v int64) {
	var start = timestamp();
	var n = fib(v)
	fmt.Printf("calc done [%v] %v=> %v [%d]\n",i, v, n, (timestamp() - start))
}

func task(ch chan int, i int, v int64) {
	calc(i, v)
	// send
	ch <- 1
}

func main() {
	ch := make(chan int)
	nums := []int64{ 42, 30, 40, 45, 40 }

	start := timestamp()
	for i,v := range nums {
		calc(i, v)
	}
	fmt.Printf("Done for loop [%v]----\n", (timestamp() - start))

	start = timestamp()
	for i,v := range nums {
		//fmt.Printf("Strat [%v] %v\n", i, v)
		go task(ch, i, v)
	}

	var counter int = 0
	for {
		select {
		case cnt := <-ch:
			counter = counter + cnt
			//fmt.Printf("Count-> %v [%v]\n", cnt, counter)
		}
		if counter == len(nums) {
			close(ch)
			fmt.Printf("Done gorutine [%v]----\n", (timestamp() - start))
			break
		}
	}
	fmt.Printf("Done program\n")
}
