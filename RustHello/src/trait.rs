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
