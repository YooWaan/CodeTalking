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

### Result<T, E>

- When returing a value, `Ok` enum is returned
- When something happens, `Err` enum is returned

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

### Option< T >

- When existing a value, `Some` enum is returned
- When nothing, `None` enum is returned

```rust
struct Dice {
    number: Number,
    next: Option<Box<Dice>>,        // <-- This is Option
}

{
    let dice = Box::new(Dice {
        number: Number::One,
        next: Some(Box::new(Dice {  // a value
            number: Number::Two,
            next: None,             // nothing
        })),
    });
}
```

Returned result is handled by match expression usually.

```rust
match dice {
    Some(d) => Ok(d),
    None => Err("No dice rolled".to_string()),
}
```

### Optional Chaining Syntax

**Result**

* If roll() returns Err enum, roll_dice() retruns Err enum without handling code

```rust
fn roll(&self) -> Result<Number, String> {
    match rand::random_range(1..=13) {
        1 | 7 => Ok(Number::One),
        2 | 8 => Ok(Number::Two),
        3 | 9 => Ok(Number::Three),
        4 | 10 => Ok(Number::Four),
        5 | 11 => Ok(Number::Five),
        6 | 12 => Ok(Number::Six),
        _ => Err("invalid number".to_string()),
    }
}

fn roll_dice(&self, times: u32) -> Result<Box<Dice>, String> {
    let mut dice = None;
    for _ in (1..times).rev() {
        let new_dice = Dice {
            number: self.roll()?,
            next: dice,
        };
        dice = Some(Box::new(new_dice));
    }

    match dice {
        Some(d) => Ok(d),
        None => Err("No dice rolled".to_string()),
    }
}
```

**Option**

* When next is a value, a value is returned. Otherwise, None is returned.

```rust
struct Dice {
    number: Number,
    next: Option<Box<Dice>>,
}

fn get_at_3rd(head: Box<Dice>) -> Option<Number> {
    Some(head.next?.next?.number)
}
```


<kbd>Snippet Result</kbd>


```bash
❯ cargo run --bin dice
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.03s
     Running `target/debug/dice`
Rolled: 3
Dices: n=0 [1], n=1 [1], n=2 [3], n=3 [1]
3rd dice number: 3
3rd dice not found
```


### Comparison

#### Result enum in Scala

* Either is similar to Result enum and match pattern control flow
* Using `for-comprehension` is similar to optional chaining syntax

```scala
def divide(a: Int, b: Int): Either[String, Int] = {
  if (b <= 0) Left("Invalid Number")
  else Right(a/b)
}

def div_example1(): Unit = {
  // Similar to match handling of Result<T, E>
  divide(10, 2) match {
    case Left(err) => println(s"Failed: $err")
    case Right(result) => println(s"Num: $result")
  }
}

def div_example2(): Unit = {
  // for-comprehension
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

```bash
❯ scala-cli pattern.sc
Num: 5
Num: Right(2)
Num: Left(Invalid Number)
~/dev-repo/github/CodeTalk
```


#### Option enum in Typescript & Zig

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

<kbd>Snippet Result</kbd>


```bash
❯ bun run option.ts
{
  num: 1,
}
{
  num: 2,
  ref: {
    num: 10,
  },
}
undefined
{
  num: 10,
}
undefined
19 | // work
20 | console.log(val1?.ref?.ref)
21 | console.log(val2?.ref)
22 | console.log(val2?.ref?.ref)
23 | // Error
24 | console.log(val1.ref.ref)
                      ^
TypeError: undefined is not an object (evaluating 'val1.ref.ref')
      at /Users/yoowaan/dev-repo/github/CodeTalking/RustHello/snippets/option.ts:24:18
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

<kbd>Snippet Result</kbd>

```bash
❯ zig run option.zig
v1=.{ .num = 1, .ref = null }
v2=.{ .num = 2, .ref = .{ .num = 1, .ref = null } }
V1.Num=1 option.Value@1015fead8p
V2.Ref=1 *const option.Value@101609dc0p
```