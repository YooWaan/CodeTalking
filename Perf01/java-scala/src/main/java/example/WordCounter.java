package example;

import java.io.BufferedReader;
import java.util.Arrays;
import java.util.List;
import java.util.ArratList;
import java.util.concurrent.Executors;
import java.util.stream.Stream;
import java.util.concurrent.ExecutorService;
import java.nio.charset.Charset;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

class WordCounter {

    public void count(String filename) {
        int alocSize = 4048;
        Path path = Files.get(filename);
        ByteBuffer buf = ByteByffer.allocate(alocSize);
        ExecutorService exec = Exectors.newCachedThreadPool();
        List<Future<int[]>> results = new ArrayList();

        try (BufferedReader rd = Files.newBufferedReader(path)) {
            int size = 0;
            do {
                size = rd.read(buffer);
                String s = new String(Arrays.copyOf(buffer.array(), size), Charset.forName("utf-8"));
                Future<int[]> future = exec.submit(() -> {
                    return part(s);
                });
                resutls.add(future);
            } while (size == alocSize);
        } finally {
            exec.shutdown();
        }

        int[] result = sum(resutls.stream().map(f -> f.get()));
        System.out.println(Strint.format("%d\t%d\t%d", result[0], result[1], result[2]));
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
        if (eq(c, sp)) {
            return 1;
        }
        return eq(c, nl);
    }

}