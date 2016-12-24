package main

import (
	"fmt"
)

// https://github.com/robpike/filter

func Filter(ff func(int) bool, data []int) []int {
	ret := make([]int, 0)
	for _, e := range data {
		if ff(e) {
			ret = append(ret, e)
		}
	}
	return ret
}

func Map(mf func(int) int, data []int) []int {
	ret := make([]int, len(data))
	for i, e := range data {
		v := mf(e)
		ret[i] = v
	}
	return ret
}

func Reduce(rf func(int, int) int, data []int) int {
	sum := 0
	for _, e := range data {
		sum = rf(sum, e)
	}
	return sum
}

func main() {
	data := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

	filter_func := func(a int) bool {
		return a%2 == 0
	}

	map_func := func(a int) int {
		return 2 * a
	}

	reduce_func := func(a int, b int) int {
		return a + b
	}

	fmt.Printf("filter-> %v\n", Filter(filter_func, data))
	fmt.Printf("filter -> map-> %v\n", Map(map_func, Filter(filter_func, data)))
	fmt.Printf("filter -> map-> reduce-> %v\n", Reduce(reduce_func, Map(map_func, Filter(filter_func, data))))

	sumCurrying := func() func([]int) int {
		return func(dat []int) int {
			return Reduce(reduce_func, Map(map_func, Filter(filter_func, data)))
		}
	}

	curFn := sumCurrying()
	fmt.Printf("currying->%v\n", curFn(data))
}
