package main

import (
	"fmt"
	"os"
)

type CallFunc func()

// ポインタ
func pointer() {
	var pi *int
	var num int = 100
	pi = &num
	fmt.Printf("01 num %v address %p pi %v\n", num, pi, *pi)

	*pi = 200
	fmt.Printf("02 num %v address %p pi %v\n", num, pi, *pi)
}

// 配列
func lst() {
	var lst = []int{1,2,3,4,5}
	for i, v := range lst {
		fmt.Printf("i=%v [%v]\n", i, v)
	}
}


// マップ
func mapVar() {
	var idname map[int]string = map[int]string{1:"aaaa", 2: "bbbb", 3:"ccc"}
	var id = 1
	fmt.Printf("Length=> %v No %v value --> %v\n", len(idname), id, idname[id])

	for k,v := range idname {
		fmt.Printf("No %v value --> %v\n", k, v)
	}
}

// エラーハンドル
func errorHandle() {
	var lst = []int{1,3,4,6,9,14,15}
	for i, v := range lst {
		r, er := check(v, "err msg")
		if er != nil {
			fmt.Printf("&&&& i=%v ret-> %v err, %v\n", i, r, er)
		} else {
			fmt.Printf("i=%v ok ret-> %v\n", i, r)
		}
	}

	fmt.Printf("Panic Sample-------\n")
	rv()
}

func check(num int, msg string) (int, error) {
	var ret = num % 3
	if ret == 0 {
		return ret , fmt.Errorf(msg, 1)
	}
	return ret, nil
}

func rv() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("Recovered in f", r)
        }
    }()
    fmt.Println("Calling err.")
    err(0)
    fmt.Println("Returned normally from err.")	
}

func err(i int) {
	if i > 3 {
        fmt.Println("Panicking!")
        panic(fmt.Sprintf("%v", i))
    }
    defer fmt.Println("Defer in err", i)
    fmt.Println("Printing in err", i)
    err(i + 1)
}



func parse(args []string) byte {
	if len(args) == 0 {
		return 0
	}

	switch (args[0]) {
	case "-p": return 0x01
	case "-l": return 0x02
	case "-m": return 0x04
	case "-e": return 0x08
	case "-a": return 0xff
	}

	return 0;
}

func ifRun(b bool, f CallFunc) {
	if b {
		f()
	}
}


func main() {
	var opt byte = parse(os.Args[1:])

	fmt.Printf("Go syntax etc opt->[%v]\n", opt)
	ifRun(opt & 0x01 > 0, pointer)
	ifRun(opt & 0x02 > 0, lst)
	ifRun(opt & 0x04 > 0, mapVar)
	ifRun(opt & 0x08 > 0, errorHandle)
}
