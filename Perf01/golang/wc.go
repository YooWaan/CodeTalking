// +build wc
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"sync"
	"unicode"
	"unicode/utf8"
)

const readSize = 4 * 1024

type Count struct {
	Lines uint64
	Words uint64
	Bytes uint64
}

func (c *Count) Add(a Count) {
	c.Lines += a.Lines
	c.Words += a.Words
	c.Bytes += a.Bytes
}

func (c *Count) UpLine()        { c.Lines += 1 }
func (c *Count) UpWord()        { c.Words += 1 }
func (c *Count) String() string { return fmt.Sprintf("%d\t%d\t%d\n", c.Bytes, c.Words, c.Lines) }

type Part struct {
	Count
	Page  uint64
	First bool
	Last  bool
}

func (p *Part) WordCount(isSpace bool) {
	if isSpace && !p.Last {
		p.UpWord()
	}
	p.Last = isSpace
}

type FileCount struct {
	FileName string
	Count
}

func isSp(r rune) bool { return unicode.IsSpace(r) }

func CountUp(page uint64, data []byte) Part {
	ds := len(data)
	part := Part{Page: page, Count: Count{Bytes: uint64(ds)}}

	r, size := utf8.DecodeRune(data[0:])
	part.First = isSp(r)
	part.WordCount(part.First)

	for i := size; i < ds; {
		r, size := utf8.DecodeRune(data[i:])
		part.WordCount(isSp(r))

		if r == '\n' {
			part.UpLine()
		}

		i += size
	}
	return part
}

func Run(filename string) (FileCount, error) {
	count := FileCount{FileName: filename}

	fp, err := os.Open(filename)
	if err != nil {
		return count, err
	}
	defer func() {
		fp.Close()
	}()

	reader := bufio.NewReader(fp)
	page := uint64(0)

	for {
		buf := make([]byte, readSize)
		n, err := reader.Read(buf)
		if n == 0 {
			break
		}

		part := CountUp(page, buf[:n])
		count.Add(part.Count)
		page += 1

		if err == io.EOF {
			break
		}
		if err != nil {
			return count, err
		}
	}

	return count, nil
}

func RunParallel(filename string) (FileCount, error) {
	done := make(chan struct{})
	defer close(done)

	count := FileCount{FileName: filename}
	if parts, err := Parallel(done, filename); err != nil {
		fmt.Errorf("%s : [%v]\n", filename, err)
		return count, err
	} else {
		for _, p := range parts {
			count.Add(p.Count)
		}
	}
	return count, nil
}

func Parallel(done <-chan struct{}, filename string) ([]Part, error) {

	fp, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	ch := make(chan Part)
	defer func() {
		fp.Close()
	}()

	var wg sync.WaitGroup
	reader := bufio.NewReader(fp)
	page := uint64(0)
	parts := make([]Part, 0)

	for {
		buf := make([]byte, readSize)
		n, err := reader.Read(buf)
		if n == 0 {
			break
		}

		wg.Add(1)
		go func(pcnt uint64, buf []byte) {
			defer wg.Done()
			part := CountUp(pcnt, buf)
			select {
			case ch <- part:
			case <-done:
			}
		}(page, buf[:n])
		page += 1

		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, err
		}
	}


	go func() {
		wg.Wait()
		close(ch)
	}()

	for p := range ch {
		parts = append(parts, p)
	}

	return parts, nil
}

func main() {
	times, _ := strconv.Atoi(os.Args[1])
	files := os.Args[2:]
	for i := 0; i < times; i++ {
		idx := i % len(files)
		result, _ := RunParallel(files[idx])
		fmt.Fprintf(os.Stderr, "i=>%d file=%s, result=%v\n", i, files[idx], result)
	}
}
