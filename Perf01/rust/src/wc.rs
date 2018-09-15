use std::env;
use std::vec::Vec;
use std::result::Result;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::sync::mpsc;
use std::thread;


fn countup(i:i64, b: &[u8]) -> (i32, i32, i32) {
    let s = std::str::from_utf8(b).unwrap();
    println!("[{}]{}",i, s);
    let cs = s.chars();
    let cnt = cs.fold((0,0,0, false), |t, ch| {

        match (ch, t.3) {
            ('\n', _) => (t.0, t.1, t.2+1, false),
            (' ', true) => (t.0+1, t.1+1, t.2, false),
            (' ', false) => (t.0+1, t.1, t.2, t.3),
            _ => (t.0+1, t.1, t.2, true),
        }
    });
    (cnt.0, cnt.1, cnt.2)
}

fn word_count(file: &String) -> i32  {
    let mut f = File::open(file).unwrap();

    let size: i64 = 30;
    let mut done = false;
    let mut i: i64 = 0;
    let (tx, rx) = mpsc::channel();

    while !done {
        //let mut buffer: [u8; 30] = [0; 30];
        let mut buffer : Box<[u8]> = Box::new([0; 30]);
        let sz: usize = match f.read(&mut buffer[..]) {
            Result::Ok(sz) => {
                let tx = tx.clone();
                thread::spawn(move || {
                    tx.send(countup(i, &buffer));
                });
                sz
            },
            Result::Err(_) => panic!("failed read file"),
        };

        done = sz != 30;
        if done == false {
            i += 1;
        }
    }

    let mut data: Vec<(i32,i32,i32)> = Vec::with_capacity(i as usize);
    for _ in 0..i {
        match rx.recv() {
            Ok(wc) => data.push(wc),
            Err(_) => panic!("failed recv data"),
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
