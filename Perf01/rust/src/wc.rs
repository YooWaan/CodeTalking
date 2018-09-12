use std::env;
use std::vec::Vec;
use std::result::Result;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::sync::mpsc;
use std::thread;

fn countup(s: &str) -> (i32, i32, i32) {
    println!("{}", s);
    (0, 0, 0)
}


fn word_count(file: &String) -> i32  {
    let mut f = File::open(file).unwrap();

    let size: i64 = 10;
    let mut done = false;
    let mut i: i64 = 0;
    let (tx, rx) = mpsc::channel();
    let mut buffer = [0; 10];

    while !done {
        match f.read(&mut buffer[..]) {
            Result::Ok(sz) => {
                let s = std::str::from_utf8(&buffer).unwrap();
                let tx = tx.clone();
                thread::spawn(move || {
                    tx.send(countup(s))
                });
                done = sz != 10;
            },
            Result::Err(_) => panic!("failed read file"),
        }

        if (!done) {
            match f.seek(SeekFrom::Current(size * i)) {
                Result::Ok(_) => i += 1,
                Result::Err(_) => panic!("failed read file"),
            }
        }
    }

    let mut data: Vec<(i32,i32,i32)> = Vec::with_capacity(i as usize);
    for _ in 0..i {
        let rs = rx.recv();
        match rs {
            Ok(wc) => data.push(wc),
            Err(e) => println!("{}", e),
        }
    }

    let cnt = data.iter().fold((0,0,0), |total,x| (total.0 + x.0, total.1 + x.1, total.2 + x.2));
    println!("{:?}", cnt);
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
