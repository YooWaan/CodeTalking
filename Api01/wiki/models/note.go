package models

import (
	"strings"
)

type (
	Note struct {
		Parent   *Note
		Children Children
		Name     string
		Title    string
		Body     string
	}

	Children []*Note

	Book struct {
		Root *Note
	}
)

func (n *Note) Add(note *Note) {
	note.Parent = n
	n.Children = append(n.Children, note)
}

func (n *Note) Update(note *Note) {
	n.Name = note.Name
	n.Title = note.Title
	n.Body = note.Body
}

func (n *Note) Unlink(name string) {
	n.Children = n.Children.Unlink(name)
}

func (ch Children) Find(name string) *Note {
	for _, c := range ch {
		if c.Name == name {
			return c
		}
	}
	return nil
}

func (ch Children) Unlink(name string) Children {
	ret := make(Children, 0, len(ch))
	for i, c := range ch {
		if c.Name != name {
			ret = append(ret, ch[i])
		}
	}
	return ret
}

func (bk *Book) Add(path string, note *Note) {
	parent := bk.Find(path)
	if parent == nil {
		path = path[:strings.LastIndex(path, "/")]
		if len(path) > 0 {
			parent = bk.Find(path)
		} else {
			parent = bk.Root
		}
	}
	if parent != nil {
		parent.Add(note)
	}
}

func (bk *Book) Update(path string, note *Note) {
	if n := bk.Find(path); n != nil {
		n.Update(note)
	}
}

func (bk *Book) Unlink(path string) {
	if n := bk.Find(path); n != nil {
		n.Parent.Unlink(n.Name)
	}
}

func (bk *Book) Find(path string) *Note {
	if len(path) == 0 {
		return nil
	}
	if path == "/" {
		return bk.Root
	}

	n := bk.Root
	for _, nm := range strings.Split(path, "/") {
		n = n.Find(nm)
		if n == nil {
			return nil
		}
	}
	return n
}
