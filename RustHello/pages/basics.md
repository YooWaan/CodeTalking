# Basics



1. Brrow
  * Each value in Rust has an owner.
  * There can only be one owner at a time.
  * When the owner goes out of scope, the value will be dropped.

<br/>

2. Trait

> Traits are similar to a feature often called interfaces in other languages, although with some differences.

<br/>

3. Result / Option

<div class="grid grid-cols-2 gap-4">
<div>

```rust
enum Result<T, E> {
    Ok(T),
    Err(E),
}
```

</div><div>

```rust
enum Option<T> {
    None,
    Some(T),
}
```
</div></div>

4. Macro

- What is macro
- Unit Testing