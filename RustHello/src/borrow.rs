fn fnline(title: &str) {
    println!("--- {title}:: {:->50}", "");
}

fn print_string(ss: &String) {
    fnline("print_string");
    println!("hi, ss: {ss}");
    let tmp = ss;
    println!("hi, tmp: {tmp}");

    println!("it work: {ss}");

    println!("ss  => Stack addr: {:p}, Heap addr: {:p}", ss, ss.as_ptr());
    println!(
        "tmp => Stack addr: {:p}, Heap addr: {:p}",
        tmp,
        tmp.as_ptr()
    );
}

fn str_case() {
    fnline("string_case");
    let ss = String::from("hello world"); // ss is owner of the string data on the heap
    let s1 = ss; // ownership of the string data is moved to s1, ss is no longer valid
    // not work
    println!("work: s1: {s1}");
    //println!("not work: ss: {{ss}}, s1: {{s1}}\ns1: {s1}");
}

fn primitive_case() {
    fnline("primitive_case");
    let x = 5; // x is a primitive. x is owner of 5
    let y = x; // y is a copy of x, both x and y are valid and own their own data
    println!("x: {x}, y: {y}");
    println!(
        "x => Stack addr: {:p} size: {}",
        &x,
        std::mem::size_of_val(&x)
    );
    println!(
        "y => Stack addr: {:p} size: {}",
        &y,
        std::mem::size_of_val(&y)
    );

    let num = Box::new(10);
    println!(
        "num => Stack addr: {:p}, Heap addr: {:p}, value: {}",
        &num, num, *num
    );
}

fn main() {
    str_case();

    let ss = String::from("hello world");
    print_string(&ss);

    primitive_case();
}
