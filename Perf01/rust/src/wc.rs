use std::env;
use std::result::Result;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;


//#[warn(unused_parens)] 
fn word_count(file: &String) -> i32  {
    let mut f = File::open(file).unwrap();

    let size: i64 = 10;
    let mut buffer = [0; 10];
    let mut done = false;

    while !done {
        let sz: usize = match f.read(&mut buffer[..]) {
            Result::Ok(sz) => {
                let s = std::str::from_utf8(&buffer).unwrap();
                println!("{}", s);
                sz;
            },
            Result::Err(_) => panic!("failed read file"),
        }

        if (sz != 10) {
            done = false;
        } else {
            f.seek(SeekFrom::Current(size));
        }
    }


    return 0;
}

fn word_counts(mut args: Vec<String>) -> i32 {
    args.remove(0);
    let times = args.remove(0).parse().unwrap();
    for n in 0..times {
        let i = n % args.len();
        //println!("n {}, i {} ==> {:?}", n, i, args.get(i));
        word_count(args.get(i).unwrap());
    }
    return 0;
}


fn main() {
    let args: Vec<String> = env::args().collect();

    println!("{:?}", args);

    std::process::exit(match args.len() {
        3 | 4 | 5 | 6 | 7 | 8 | 9 => word_counts(args),
        _ => {
            println!("cmd num files...");
            0
        },
    });
}
