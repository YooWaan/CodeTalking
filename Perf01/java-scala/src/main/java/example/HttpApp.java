package example;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutionException;
import java.util.stream.Stream;

import java.nio.CharBuffer;
import java.nio.charset.Charset;

import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpExchange;

public class HttpApp {

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(5100), 0);
        server.createContext("/", new WordWebApp());
        server.start();
    }
}

class WordWebApp implements HttpHandler {

    final int OK = 200;

    public void handle(HttpExchange ex) throws IOException {
        try {
            Integer length = Integer.valueOf(ex.getRequestHeaders().getFirst("Content-Length"));
            byte[] body = count(ex.getRequestBody(), length);
            
            ex.sendResponseHeaders(OK, body.length);
            try (OutputStream out = ex.getResponseBody()) {
                out.write(body);
            }
        } catch (InterruptedException e) {
            byte[] body = "failed".getBytes();
            ex.sendResponseHeaders(OK, body.length);
            ex.getResponseBody().write(body);
        }
    }

    public byte[] count(InputStream in, int contentLength) throws IOException, InterruptedException {

        List<Future<int[]>> results = new ArrayList();
        ExecutorService exec = Executors.newCachedThreadPool();

        try {
            int offset = 0;
            int alocSize = 4048;
            int size = 0;
            byte[] buffer = new byte[alocSize];
            do {
                size = in.read(buffer);
                offset += size;
                //System.out.println(">>>>>>off" + offset + ", size=" + size + ", clen?:" + (offset<contentLength));
                String s = new String(buffer, 0, size);
                results.add(exec.submit(() -> {return part(s);}));
            } while (offset < contentLength);
        } finally {
            in.close();
            exec.shutdown();
        }

        return reduce(results.stream().map(this::futureGet));
    }

    int[] futureGet(Future<int[]> f) {
        try {
            return f.get();
        } catch (InterruptedException | ExecutionException e) {
            return new int[]{0,0,0};
        }
    }

    int[] part(String s) {
        return sum(s.chars()
        .mapToObj(i -> {
            char ch = s.charAt(i);
            return new int[]{1, wd(ch, ' ', '\n'), eq(ch, '\n')};
        }));
    }

    int[] sum(Stream<int[]> s) {
        final int[] ret = new int[]{0, 0, 0};
        s.forEach(n -> {
            ret[0] += n[0]; ret[1] += n[1]; ret[2] += n[2];            
        });
        return ret;
    }

    byte[] reduce(Stream<int[]> s) {
        int[] ret = sum(s);
        return String.format("%d\t%d\t%d", ret[0], ret[1], ret[2]).getBytes();
    }

    int eq(char c, char e) {
        return c == e ? 1 : 0 ;
    }

    int wd(char c, char sp, char nl) {
        if (eq(c, sp) == 1) {
            return 1;
        }
        return eq(c, nl);
    }

}   
