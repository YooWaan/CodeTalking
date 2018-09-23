
use std::net::{TcpStream, TcpListener};
use std::io::{Read,Write};
use std::sync::mpsc;
use std::thread;
use std::sync::atomic::{self, AtomicUsize, Ordering};

static COUNTER: AtomicUsize = AtomicUsize::new(0);


fn countup(b: &[u8]) -> (i32, i32, i32, bool) {
    let s = std::str::from_utf8(b).unwrap();
    //println!("[{}]{}",i, s);
    let cs = s.chars();
    return cs.fold((b.len() as i32, 0,0, false), |t, ch| {
        match (ch, t.3) {
            ('\n', _) => (t.0, t.1, t.2+1, false),
            (' ', true) => (t.0, t.1+1, t.2, false),
            (' ', false) => (t.0, t.1, t.2, t.3),
            _ => (t.0, t.1, t.2, true),
        }
    });
}

fn handle_client(mut stream: TcpStream) {
    let mut data: Vec<(i32,i32,i32,bool)> = Vec::new();
    {
        let size: i64 = 2048;
        let mut done = false;
        let mut i: i64 = 0;
        let (tx, rx) = mpsc::channel();

        while !done {
            //let mut buffer: [u8; 30] = [0; 30];
            let mut buffer : Box<[u8]> = Box::new([0; 2048]);
            let rr = stream.read(&mut buffer[..]);
            let sz: usize = match rr {
                Result::Ok(sz) => sz,
                Result::Err(_) => panic!("failed read file"),
            };
            let tx = tx.clone();
            thread::spawn(move || {
                tx.send(countup(&buffer[..sz]));
            });
            i += 1;
            done = sz != size as usize;
        }

        for _ in 0..i {
            match rx.recv() {
                Ok(wc) => data.push(wc),
                Err(_) => panic!("failed recv data"),
            }
        }
    }

    let cnt = data.iter().fold((0,0,0), |total,x| (total.0 + x.0, total.1 + x.1, total.2 + x.2));
    let content = format!("{}\t{}\t{}", cnt.0, cnt.1, cnt.2);
    let res = format!("HTTP/1.1 200 OK\r\nContent-Type: text/plan; charset=UTF-8\r\nContent-Length: {}\r\nConnection: close\r\n\r\n{}", content.len(), content);

    let sended = match stream.write(res.as_bytes()) {
        Ok(sz) => sz,
        Err(e) => {
            println!("Failed sending response: {}", e);
            0
        },
    };
    if sended > 0 {
        COUNTER.fetch_add(1, atomic::Ordering::SeqCst);
    }
}

pub fn main() {
    let listener = TcpListener::bind("127.0.0.1:5100").unwrap();
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                thread::spawn(move || {
                    handle_client(stream)
                });
            }
            Err(_) => { panic!("connection failed") }
        };

        let c = COUNTER.load(Ordering::Relaxed);
        if c >= 1000 {
            break;
        }
    }
}
