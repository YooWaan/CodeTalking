package main

import (
	"fmt"
	"structsinterface/value"
)

func main() {
	// a = 5 b= 5 c=1.5
	var a value.Value = value.NewInt(5)
	var b value.Value = value.NewInt(5)
	var c value.Value = value.NewFloat(1.5)
	fmt.Printf("a=%v b=%v c=%v\n", a, b, c)

	// Answer = (a + b) * c
	var expr value.Expr = value.NewMul( value.NewAdd(a, b) , c)
	fmt.Printf("Int=%v\n", expr.CalcI())
	fmt.Printf("Float=%v\n", expr.CalcF())
}
