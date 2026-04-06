## Enums & Pattern Matching

This section goes through these major enums.

### Result & Option

```rust
enum Result<T, E> {           
    Ok(T),  // Success
    Err(E), // Failure
}

enum Option {
    None,    // nothing
    Some(T), // a value
}
```

- When returing a value, Ok enum is returned
- When nothing, Err enum is returned

```rust
impl Hand {
    fn roll(&self) -> Result<Number, String> {
        match rand::random_range(1..=13) {
            1 => Ok(Number::One),
               :
            6 => Ok(Number::Six),
            _ => Err("invalid number".to_string()),
        }
    }
}
```

Returned result is handled by match expression usually.


```rust
match hand.roll() {
    Ok(num) => println!("Rolled: {:?}", num),
    Err(e) => println!("Error rolling dice: {}", e),
}
```

### Comparison with Scala at Result enum


```scala
def divide(a: Int, b: Int): Either[String, Int] = {
  if (b <= 0) Left("Invalid Number")
  else Right(a/b)
}

def div_example1(): Unit = {
  divide(10, 2) match {
    case Left(err) => println(s"Failed: $err")
    case Right(result) => println(s"Num: $result")
  }
}

def div_example2(): Unit = {
  var num = for {
    a <- divide(10, 2)
    b <- divide(a, 2)
  } yield b

  println(s"Num: $num")

  num = for {
    a <- divide(10, 2)
    b <- divide(a, 0)
  } yield b
  println(s"Num: $num")
}
```


### Comparison with Typescript & Zig at Option enum

<kbd>Typescript</kbd>

```typescript
interface Value {
    num: number
    ref: Value | undefined
}

let val1 = {
    num: 1,
} as Value;

let val2 = {
    num: 2,
    ref: {
        num: 10,
    },
} as Value;

console.log(val1);
console.log(val2);
// work
console.log(val1?.ref?.ref)
console.log(val2?.ref)
console.log(val2?.ref?.ref)
// Error
console.log(val1.ref.ref)
```

<kbd>Zig</kbd>

```zig
const std = @import("std");

const Value = struct {
    num: u32,
    ref: ?*const Value,  // <--- Zig is possible to define Option type with '?'
};

pub fn main() void {
    const v1: Value = Value{
        .num = 1,
        .ref = null,
    };

    const v2 = Value{
        .num = 2,
        .ref = &v1,
    };

    std.debug.print("v1={}\n", .{v1});
    std.debug.print("v2={}\n", .{v2});

    // conditional option value handling
    if (v1.ref) |val| {
        std.debug.print("V1.Ref={} {*}p\n", .{val.num, &val});
    } else {
        std.debug.print("V1.Num={} {*}p\n", .{v1.num, &v1});
    }

    // conditional option value handling
    if (v2.ref) |val| {
        std.debug.print("V2.Ref={} {*}p\n", .{val.num, &val});
    } else {
        std.debug.print("V2.Num={} {*}p\n", .{v2.num, &v2});
    }
}
```