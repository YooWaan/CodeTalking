package main

import "fmt"

type Number struct {
	Name  string
	Value int
}

func main() {
	v1 := Number{"one", 1}
	v2 := v1

	fmt.Printf(" v1   [%p] [%v] %p=>%d\n", &v1, v1, &v1.Value, v1.Value)
	fmt.Printf(" v2   [%p] [%v] %p=>%d\n", &v2, v2, &v2.Value, v2.Value)

	v3 := make([]Number, 1)
	_ = copy(v3, []Number{v1})

	fmt.Printf("v3[0] [%p] [%v] %p=>%d\n", &v3[0], v3[0], &v3[0].Value, v3[0].Value)
}
