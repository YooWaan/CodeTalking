package ql

import (
	"context"
	"encoding/json"
	"log"

	"note.mem/wiki/app"
)

var (
	keyBook = struct{ Name string }{"key_book"}
)

func Book(c context.Context) *app.Book {
	b, _ := c.Value(keyBook).(*app.Book)
	return b
}

func WithBook(c context.Context) context.Context {

	root := fromJSON(`{"name": "/", "title": "Wiki", "text": "Hello",
"children": [
  {"name": "one", "title": "one", "text": "one", "children": [
    {"name": "three", "title": "three", "text": "three"}
  ]},
  {"name": "two", "title": "two", "text": "two"}
]}`)

	b := &app.Book{Root: root}
	return context.WithValue(c, keyBook, b)
}

func Search(c context.Context, path string) *Page {
	book := Book(c)
	note := book.Find(path)
	return &Page{
		Path: path,
		Note: newNote(note),
	}
}

func Tree(c context.Context, page *Page, depth *int) []*Page {
	if page == nil || depth == nil || *depth == 0 {
		return []*Page{}
	}

	book := Book(c)
	note := book.Find(page.Path)
	log.Printf("Tree ==> %v", page.Path)
	note = note.Tree(*depth)

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
	ch := make([]*Page, len(note.Children))
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
		Name:  note.Name,
		Title: note.Title,
		Text:  note.Body,
	}
}

func fromJSON(jsonStr string) *app.Note {
	root := &app.Note{
		Name:  "/",
		Title: "Wiki",
		Body:  "Hello",
	}

	//data := map[string]string{}
	data := make(map[string]interface{})
	_ = json.Unmarshal([]byte(jsonStr), &data)
	mapToNote(root, data)
	return root
}

func mapToNote(parent *app.Note, val map[string]interface{}) {
	title := val["title"].(string)
	text := val["text"].(string)
	name := val["name"].(string)

	parent.Title = title
	parent.Body = text
	parent.Name = name

	if v, ok := val["children"]; ok {
		nodes := v.([]interface{})
		cs := make(app.Children, len(nodes))
		for i, node := range nodes {
			data := node.(map[string]interface{})
			child := &app.Note{Parent: parent}
			mapToNote(child, data)
			cs[i] = child
		}
		parent.Children = cs
	}
}
