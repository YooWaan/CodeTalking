

macro_rules! arr_fn {
    ($size:expr, $func:expr) => {
        {
            let func = $func;
            let mut array: [_; $size] = std::mem::uninitialized();
            let xs = std::ops::Range {start:1, end:$size + 1};
            for i in xs {
                std::ptr::write(&mut array[i-1], func(i));
            }
            array
        }
    };
}

macro_rules! left {
    ($N:expr) => {
        unsafe {
            let mut mx: [_; $N] = std::mem::uninitialized();
            let xs = std::ops::Range {start:1, end:$N + 1};
            //const CSZ: usize = $N - 1;
            for i in xs {
                let xf = |_|{ i };
                // |arg| (i) as i32
                mx[i-1] = arr_fn!($N, xf);
            }
            mx
        }
    };
}

macro_rules! right {
    ($N:expr) => {
        unsafe {
            let mut mx: [_; $N] = std::mem::uninitialized();
            let xs = std::ops::Range {start:1, end:$N + 1};
            //const CSZ: usize = $N - 1;
            for i in xs {
                mx[i-1] = arr_fn!($N, |arg| (arg) as i32);
            }
            mx
        }
    };
}

fn main() {
    const SZ: usize = 4;
    //let a: [i32; SZ] = arr_fn!(SZ, |i| (i) as i32);
    //let xs = std::ops::Range {start:3, end:10};
    //println!("Hello, world! {:?}", a);
    let l = left!(SZ);
    let r = right!(SZ);
    println!("Hello, world! {:?}", l);
    println!("{:?}", r);
}
