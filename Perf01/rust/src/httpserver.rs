

use std::net::{TcpStream, TcpListener};
use std::io::{ Write};
use std::thread;

fn handle_client(mut stream: TcpStream) {
    //let mut stream = io::BufReader::new(stream);

    let response = b"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<html><body>Hello world</body></html>\r\n";
    match stream.write(response) {
        Ok(_) => println!("Response sent"),
        Err(e) => println!("Failed sending response: {}", e),
    }
}

pub fn serve(bindhost: String) {
    let listener = TcpListener::bind(bindhost).unwrap();

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                thread::spawn(move || {
                    handle_client(stream)
                });
            }
            Err(_) => { panic!("connection failed") }
        };
    }
}