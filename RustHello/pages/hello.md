# Hello, World


## Characteristics of Rust

<span class="red">red colored phrases</span> are explained in `2. Basic`. And the ecosystem of rust is covered in the next section.

These 3 keys are described at `Why Rust?` in [rust-lang.org](https://rust-lang.org/)

**Performance**

Rust is blazingly fast and memory-efficient: with <span class="text-lg red">no runtime or garbage collector</span>, it can power performance-critical services, run on embedded devices, and easily integrate with other languages.

<hr/>

**Reliability**

Rust’s rich type system and ownership model guarantee <span class="text-lg red">memory-safety</span> and <span class="text-lg red">thread-safety</span> — enabling you to eliminate many classes of bugs at compile-time.


<hr/>

**Productivity**

Rust has great documentation, a friendly compiler with useful error messages, and top-notch tooling — an integrated package manager and build tool, smart multi-editor support with auto-completion and type inspections, an auto-formatter, and more.



## Rust Eco System


| Command | Description |
| ------- | ---- |
| cargo   |  Package Manager |
| rustup  |  Tool Chain Installer |
| rustc   |  Compiler |
| clippy  |  Linter |
| rustfmt |  Formatter |


---

## Hello World

<iframe src="https://play.rust-lang.org/?version=stable&mode=debug&edition=2021" width="100%" height="450px"></iframe>

---

## Helloworld in terminal

<div class="grid grid-cols-2 gap-4">
<div>

```bash
# run
cargo run --bin hello

# build
cargo build --release --bin hello

# rustc
rustc src/hello.rs && ./hello


# clean
cargo clean
```
</div>

<div>

```bash
target
├── CACHEDIR.TAG
└── release
    ├── build
    ├── deps
    │   ├── hello-bf50690d000b3ddc
    │   └── hello-bf50690d000b3ddc.d
    ├── examples
    ├── hello
    ├── hello.d
    └── incremental
```

</div></div>
