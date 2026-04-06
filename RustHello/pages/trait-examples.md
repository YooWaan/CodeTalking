## Trait Examples


| Trait | Description |
| --- | ---- |
| `Debug	#[derive(Debug)]` | Print content of variable by `{}` |
| `Display` | Print content of variable by `{:?}` |
| `Clone	#[derive(Clone)]` | Clone itself |
| `Copy	#[derive(Copy)]` | Copy itself |
| `PartialEq	#[derive(PartialEq)]` | Enable to compare a struct with '==' operator	|


---

### Debug, Clone, Copy

<kbd>Rust</kbd>

```rust
#[derive(Clone)]
struct Value {
    name: String,
    num: i32,
}

impl std::fmt::Display for Value {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Value {{ name: {}, num: {} }}", self.name, self.num)
    }
}

#[derive(Debug, Copy)]
struct Pretty<'a> {
    name: &'a str,
    num: i32,
}

impl<'a> Clone for Pretty<'a> {
    fn clone(&self) -> Self {
        Self {
            name: self.name,
            num: self.num,
        }
    }
}

fn main() {
    let v1 = Value {
        name: String::from("v1"),
        num: 10,
    };
    println!(
        "Display={} value={}, {} ptr[{:p}, {:p}, {:p}]",
        v1, v1.name, v1.num, &v1, &v1.name, &v1.num
    );

    let v2 = v1.clone();
    println!(
        "Cloned value={}, {} ptr[{:p}, {:p}, {:p}]",
        v2.name, v2.num, &v2, &v2.name, &v2.num
    );

    let p1 = Pretty {
        name: "p1",
        num: 30,
    };
    println!(
        "pretty 1={:?} ptr[{:p}, {:p}, {:p}, {:p}]",
        p1, &p1, &p1, &p1.name, &p1.num
    );

    let p2 = p1;
    println!(
        "pretty 2={:?} ptr[{:p}, {:p}, {:p}, {:p}]",
        p2, &p2, &p2, &p2.name, &p2.num
    );
}
```

---

<kbd>Golang</kbd>


```go
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
```


```bash
❯ go run snippets/trait.go
 v1   [0xf7df58ce018] [{one 1}] 0xf7df58ce028=>1
 v2   [0xf7df58ce030] [{one 1}] 0xf7df58ce040=>1
v3[0] [0xf7df58ce078] [{one 1}] 0xf7df58ce088=>1
```

