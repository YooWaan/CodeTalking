## Ownership & Borrowing Examples


<style>
code {
    font-size: 11px;
}
</style>


### Ownership


<kbd>borrow.rs</kbd>

```rust
fn str_case() {
    let ss = String::from("hello world");  // ss is owner of the string data on the heap
    let s1 = ss;                           // ownership of the string data is moved to s1, ss is no longer valid
    // not work 
    println!("ss: {ss}, s1: {s1}");
}

fn primitive_case() {
    let x = 5;                  // x is a primitive. x is owner of 5
    let y = x;                  // y is a copy of x, both x and y are valid and own their own data
    println!("x: {x}, y: {y}");
}
```

<kbd>Error Message</kbd>

```bash
21 |     let ss = String::from("hello world");  // ss is owner of the string data on the heap
   |         -- move occurs because `ss` has type `String`, which does not implement the `Copy` trait
22 |     let s1 = ss;                           // ownership of the string data is moved to s1, ss is no longer valid
   |              -- value moved here
23 |     // not work
24 |     println!("ss: {ss}, s1: {s1}");
   |                    ^^ value borrowed here after move
```


---

### Immutable and Mutable


<kbd>Rust</kbd>

<ul class="text-xs">
<li><b>let</b> is immutable</li>
<li><b>mut allow</b> to modify value</li>
</ul>

```rust
struct Number {
    value: i32,
}

fn example() {
    {
        let num = Number { value: 10 };
        // cannot modify num.value
        // num.value += 5;
        println!("     let Number: {:p}, Value: [{:p}]: {}", &num, &num.value, num.value);
    }

    {
        let mut num = Number { value: 20 };
        // can modify num.value
        num.value += 5;
        println!("Mutable  Number: {:p}, Value: [{:p}]: {}", &num, &num.value, num.value);
        num.value += 10;
        println!("Mutable  Number: {:p}, Value: [{:p}]: {}", &num, &num.value, num.value);
    }
}
```


<kbd>C++</kbd>

- `const` is immutable
- variable is mutable

```c++

struct Number {
    int value;

    ~Number() {
        std::cout << "Destruct:[" << (void*)this << "] [value: " << &value << "] " << value << std::endl;
    }
};

    {
        const Number n = { 10 };
        line("const Number");
        std::cout << "Number:  [" << &n << "] [value: " << &n.value << "] " << n.value << std::endl;

        //const Number* p = &n;
        //p->value = 100; // Error: assignment of read-only member 'Number::value'
    }

    {
        line("Number Variable");
        Number num = { 20 };
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
        num.value += 5;
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
        num.value += 10;
        std::cout << "Number:  [" << &num << "] [value: " << &num.value << "] " << num.value << std::endl;
    }
```

<kbd>Snippet Result</kbd>

```bash
❯ g++ -o bor1 ./borrow.cpp && ./bor1
--- print_string:: --------------------------------------------------
hi, ss: hello world
hi, tmp: hello world
 borrowed value is no there
 ss => Stack addr: 0x7ff7bac4ec18, Heap addr: 0x1052b0660,value: hello world
tmp => Stack addr: 0x7ff7bac4ec10, Heap addr: 0x1052b0660,value: hello world
```

---

### Smart Pointers


<kbd>Rust</kbd>

```rust
    {
        let num = std::cell::RefCell::new(Number { value: 30 }); // Box to allocate num on the heap
        num.borrow_mut().value += 5; // Modify the value through mutable reference
        println!("Mutable  Number: ...");
        num.borrow_mut().value += 10; // Modify the value through mutable reference again
        println!("Mutable  Number: ...");
    }

    {
        let num = std::rc::Rc::new(Number { value: 40 });

        let s: &Number = &num;
        println!("Rc<Number>: {:p}", s);

        {
            let num_clone = std::rc::Rc::clone(&num);
            println!("Rc<Number> Clone: {:p} {}, Strong Count: {}", std::rc::Rc::as_ptr(&num_clone), &num_clone.value, std::rc::Rc::strong_count(&num_clone));
        }

        {
            let num_clone = std::rc::Rc::clone(&num);
            println!("Rc<Number> Clone: {:p} {}, Strong Count: {}", std::rc::Rc::as_ptr(&num_clone), &num_clone.value, std::rc::Rc::strong_count(&num_clone));
        }
    }
```

<kbd>Snippet Result</kbd>

```bash
❯ cargo run --bin bor2
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.03s
     Running `target/debug/bor2`
--- let Number:: --------------------------------------------------
     let Number: 0x7ff7b56ff18c, Value: [0x7ff7b56ff18c]: 10
Dropping Number [0x7ff7b56ff18c] with value: 10
--- let mut Number:: --------------------------------------------------
Mutable  Number: 0x7ff7b56ff21c, Value: [0x7ff7b56ff21c]: 25
Mutable  Number: 0x7ff7b56ff21c, Value: [0x7ff7b56ff21c]: 35
Dropping Number [0x7ff7b56ff21c] with value: 35
--- RefCall Number with reference:: --------------------------------------------------
Mutable  Number: 0x7ff7b56ff330, Value: [0x7ff7b56ff338]: 35
Mutable  Number: 0x7ff7b56ff330, Value: [0x7ff7b56ff338]: 45
Dropping Number [0x7ff7b56ff338] with value: 45
--- Rc<Number>:: --------------------------------------------------
Rc<Number>: 0x6000027851b0
Rc<Number> Clone: 0x6000027851b0 40, Strong Count: 2
Rc<Number> Clone: 0x6000027851b0 40, Strong Count: 2
Dropping Number [0x6000027851b0] with value: 40
```

<kbd>C++</kbd>

```c++
    {
        line("unique ptr Number*");
        std::unique_ptr<Number> p = std::make_unique<Number>();
        p->value = 30;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
        p->value += 5;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
        p->value += 10;
        std::cout << "Number:  [" << p << "] [value: " << &p->value << "] " << p->value << std::endl;
    }

    {
        line("shared ptr Number*");
        std::shared_ptr<Number> p = std::make_shared<Number>();
        p->value = 40;
        std::cout << "Shared_ptr<Number>: [" << p << "] [value: " << &p->value << "] " << p->value << ", Use Count: " << p.use_count() << std::endl;

        {
            std::shared_ptr<Number> s_p = p;
            std::cout << "Shared_ptr<Number> Clone: [" << s_p << "] [value: " << &s_p->value << "] " << s_p->value << ", Use Count: " << s_p.use_count() << std::endl;
        }

        {
            std::shared_ptr<Number> s_p = p;
            std::cout << "Shared_ptr<Number> Clone: [" << s_p << "] [value: " << &s_p->value << "] " << s_p->value << ", Use Count: " << s_p.use_count() << std::endl;
        }

    }
```


<kbd>Snippet Result</kbd>

```bash
❯ g++ -o bor2 ./borrow-2.cpp && ./bor2
--- const Number:: --------------------------------------------------
Number:  [0x7ff7ba259c38] [value: 0x7ff7ba259c38] 10
Destruct:[0x7ff7ba259c38] [value: 0x7ff7ba259c38] 10
--- Number Variable:: --------------------------------------------------
Number:  [0x7ff7ba259c28] [value: 0x7ff7ba259c28] 20
Number:  [0x7ff7ba259c28] [value: 0x7ff7ba259c28] 25
Number:  [0x7ff7ba259c28] [value: 0x7ff7ba259c28] 35
Destruct:[0x7ff7ba259c28] [value: 0x7ff7ba259c28] 35
--- unique ptr Number*:: --------------------------------------------------
Number:  [0x60000342c010] [value: 0x60000342c010] 30
Number:  [0x60000342c010] [value: 0x60000342c010] 35
Number:  [0x60000342c010] [value: 0x60000342c010] 45
Destruct:[0x60000342c010] [value: 0x60000342c010] 45
--- shared ptr Number*:: --------------------------------------------------
Shared_ptr<Number>: [0x600003620038] [value: 0x600003620038] 40, Use Count: 1
Shared_ptr<Number> Clone: [0x600003620038] [value: 0x600003620038] 40, Use Count: 2
Shared_ptr<Number> Clone: [0x600003620038] [value: 0x600003620038] 40, Use Count: 2
Destruct:[0x600003620038] [value: 0x600003620038] 40
```