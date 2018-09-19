package example;

import java.io.BufferedReader;
import java.io.IOException;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutionException;
import java.util.stream.Stream;
import java.util.stream.IntStream;
import java.util.stream.Collectors;

import java.nio.CharBuffer;
import java.nio.charset.Charset;
//import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class WordCounter {

    public static void main(String[] args) {
        if (args.length <= 1) {
            System.out.println("args:" + args.length + "cmd start end\ncmd port\ncmd num files");
        } else {
            List<String> files = Arrays.stream(args).collect(Collectors.toList());
            new WordCounter()
                .run(Integer.valueOf(files.remove(0)).intValue(), files);
        }
    }

    public void run(int times, List<String> files) {
        IntStream.range(0, times)
            .forEach(i -> {
                    try {
                        count(files.get(i % files.size()));
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                });
    }


    public void count(String filename) throws IOException, InterruptedException {
        int alocSize = 4048;
        Path path = Paths.get(filename);
        CharBuffer buf = CharBuffer.allocate(alocSize);
        ExecutorService exec = Executors.newCachedThreadPool();
        List<Future<int[]>> results = new ArrayList();

        try (BufferedReader rd = Files.newBufferedReader(path)) {
            int size = 0;
            //buf.reset();
            do {
                size = rd.read(buf);
                String s = buf.toString();
                Future<int[]> future = exec.submit(() -> {
                    return part(s);
                });
                results.add(future);
            } while (size == alocSize);
        } finally {
            exec.shutdown();
        }

        int[] result = sum(results.stream().map(this::futureGet));
        System.out.println(String.format("%d\t%d\t%d", result[0], result[1], result[2]));
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
