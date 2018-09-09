
use std::vec::Vec;
use std::ops::Range;
use std::sync::mpsc;
use std::thread;
use std::env;

fn mat(sz: usize, f :fn(usize, usize) -> i32) -> Vec<Vec<i32>> {
    let mut ret: Vec<Vec<i32>> = Vec::with_capacity(sz);
    let rs = Range{start:0, end:sz};
    for i in rs {
        let xs = Range {start:1, end:sz + 1};
        let mut col: Vec<i32> = Vec::with_capacity(sz);
        for x in xs {
            col.push(f(i+1, x))
        }
        ret.push(col)
    }
    ret
}

fn mul(left:Vec<Vec<i32>>, right:Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let mut ret = Vec::with_capacity(left.len());
    for i in 0..left.len() {
        let mut data = Vec::with_capacity(right.len());
        for n in 0..right.len() {
            let mut val :i32 = 0;
            for m in 0..right.len() {
                val += left[i][m] * right[m][n];
            }
            data.push(val);
        }
        ret.push(data);
    }
    ret
}

/*
fn show(m :Vec<Vec<i32>>) {
    for r in m {
        println!("{:?}", r)
    }
}
*/

fn matrix(start :u32, end :u32) -> i32 {

    /*
    const SZ: usize = 100;
    let mut nums = Vec::with_capacity(SZ);
    for i in 1..SZ+1 {
        nums.push(i);
    }
    */

    let (tx, rx) = mpsc::channel();
    //for &n in nums.iter() {

    for n in start..end+1 {
        let tx = tx.clone();
        thread::spawn(move || {
            let row = |r:usize,_:usize| -> i32{ r as i32 };
            let col = |_:usize,c:usize| -> i32{ c as i32 };

            let size = n as usize;

            let lf = mat(size, row);
            let rg = mat(size, col);
            let ans = mul(lf, rg);
            tx.send(ans.len() == size)
        });
    }

    let mut count = 0;
    //for _ in nums.iter() {
    for _ in start..end+1 {
        let rs = rx.recv();
        match rs {
            Ok(_) => count += 1,
            Err(e) => println!("{}", e),
        }
    }

    if count == end-start+1 {
        return 0;
    }
    return 1;
}

fn num(n :Option<&String>) -> u32 {
    return n.unwrap().parse().unwrap()
}

fn main() {
    let args: Vec<String> = env::args().collect();

    //println!("{:?}", args);
    std::process::exit(match args.len() {
        3 => matrix(num(args.get(1)), num(args.get(2))),
        _ => {
            println!("cmd start end\ncmd port \ncmd num files...");
            0
        }
    });
}
