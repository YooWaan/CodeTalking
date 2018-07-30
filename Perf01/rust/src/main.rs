

macro_rules! arr_fn {
    ($size:expr, $func:expr) => {
        {
            let func = $func;
            let mut array: [_; $size] = std::mem::uninitialized();
            let xs = std::ops::Range {start:1, end:$size};
            for i in xs {
                std::ptr::write(&mut array[i], func(i));
            }
            array
        }
    };
}

macro_rules! left {
    ($N:expr) => {
        unsafe {
            let mut mx: [_; $N] = std::mem::uninitialized();
            let xs = std::ops::Range {start:1, end:$N};
            //const CSZ: usize = $N - 1;
            for i in xs {
                mx[i] = arr_fn!($N, |i| (i) as i32);
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
    let mx = left!(SZ);
    println!("Hello, world! {:?}", mx);
}
