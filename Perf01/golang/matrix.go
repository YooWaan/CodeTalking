package main

func mul(l, r [][]int) []int {
	sz = len(l)
	ans := make([]int, sz)
	for i := 1; i < sz; i++ {
		v := 0
		for n := 1; n < sz; n++ {
			v += l[i][n] * r[n][i]
		}
		ans[i] = v
	}
	return ans
}

func left(sz int) [][]int {
	ret := make([][]int, sz)
	for i := 1; i < sz+1; i++ {
		row = make([]int, sz)
		for n := 1; n < sz+1; n++ {
			row[n] = i
		}
		ret[i] = row
	}
	return ret
}

func right(sz int) [][]int {
	ret := make([][]int, sz)
	for i := 1; i < sz+1; i++ {
		row = make([]int, sz)
		for n := 1; n < sz+1; n++ {
			row[n] = n
		}
		ret[i] = row
	}
	return ret
}

func main() {

}
