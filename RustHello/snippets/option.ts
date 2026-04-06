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
