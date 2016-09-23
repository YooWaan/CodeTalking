package main

import (
	"fmt"
)

func GetClosure() func() int {
	i := 0
	inc := func() int {
		i++
		return i
	}
	return inc
}


func main() {

	n := func(x, y int) int { return x + y }(3,2)
	fmt.Printf("calc %d\n", n)

	f := func(x, y int) int { return x + y }
	fmt.Printf("func %d\n", f(3,2))

	c := GetClosure()
	fmt.Printf("inc 1 -> %d\n", c())
	fmt.Printf("inc 2 -> %d\n", c())
	fmt.Printf("inc 3 -> %d\n", c())

}
