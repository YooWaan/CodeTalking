package ql

import (
	"context"

	"note.mem/wiki/app"
)

var (
	keyBook = struct{Name string}{"key_book"}
)

func Book(c context.Context) *app.Book {
	b, _ := c.Value(keyBook).(*app.Book)
	return b
}

func WithBook(c context.Context) context.Context {
	b := &app.Book{
		Root: &app.Note{
			Name: "/",
			Title: "Wiki",
			Body: "Hello",
		},
	}
	return context.WithValue(c, keyBook, b)
}

func Search(c context.Context, path string) *Page {
	book := Book(c)
	note := book.Find(path)
	return newPage(path, note)
}

func Tree(c context.Context, page *Page, depth *int) []*Page {
	if page == nil || depth == nil || *depth == 0 {
		return []*Page{}
	}

	book := Book(c)
	note := book.Find(page.Path).Tree(*depth)

	ret := make([]*Page, len(note.Children))
	for i, ch := range note.Children {
		ret[i] = toPage(page.Path, ch)
	}
	// FIXME
	//page.Notes = ret
	return ret
}


func toPage(path string, note *app.Note) *Page {
	n := newPage(path, note)
	tree(note, n)
	return n
}

func tree(note *app.Note, n *Page) {
	if len(note.Children) == 0 {
		return
	}
	ch := make([]*Page, 0, len(note.Children))
	for i, c := range note.Children {
		child := newPage(n.Path, c)
		ch[i] = child
		tree(c, child)
	}
	n.Notes = ch
}

func newPage(path string, note *app.Note) *Page {
	pagePath := path + "/" + note.Name
	if note.Parent == nil {
		pagePath = "/"
	} else if path == "/" {
		pagePath = "/" + note.Name
	}
	return &Page{
		Path: pagePath,
		Note: newNote(note),
	}
}

func newNote(note *app.Note) *Note {
	return &Note{
		Name: note.Name,
		Title: note.Title,
		Text: note.Body,
	}
}
