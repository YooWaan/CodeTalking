package example;

import java.io.IOException;

import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpExchange;



class WordCounter implements HttpHandler {

    final int OK = 200;

    public void handle(HttpExchange ex) throws IOException {

        byte[] data = "Hello!!".getBytes();

        ex.sendResponseHeaders(OK, data.length);
        ex.getResponseBody().write(data);
        ex.getRequestBody().close();
    }
}   
