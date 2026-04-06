## Macro


- Declaretive Macros: `format!`, `println!`
- Procedual Macros
  - Custom derive Macros
  - Attribute-Like Macros
  - Function-Like Macros


```grammar
InnerAttribute -> `#` `!` `[` Attr `]`

OuterAttribute -> `#` `[` Attr `]`

Attr ->
      SimplePath AttrInput?
    | `unsafe` `(` SimplePath AttrInput? `)`

AttrInput ->
      DelimTokenTree
    | `=` Expression
```


## Testing

Testing code is written with `#cfg(test)` as the tests module generally.
If your crate is a library, to verify whether a function is callable from the library user code, it might be better to have `tests` dir separately.

```rust
pub fn add(a: u32, b: u32) -> u32 {
    a + b
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add() {
        assert_eq!(add(2, 3), 5);
    }
}
```