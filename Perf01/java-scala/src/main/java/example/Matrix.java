package example;

import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class Matrix {

    public void calc() {
        long start = System.nanoTime();
        IntStream.range(1, 100)
        .forEach(sz -> {
            int[] ans = mul(left(sz), right(sz));
        });
        System.out.println("Time:" + (System.nanoTime() - start) / 1000 + " msec");
    }

    int[] mul(int[][] left, int[][] right) {
        int sz = left.length;
        int[] ans = new int[sz];
        for (int ii = 0; ii < sz ;ii++) {
            int v = 0;
            for (int nn = 0; nn < sz ;nn++) {
                v += left[ii][nn] * right[nn][ii];
            }
            ans[ii] = v;
        }
        return ans;
    }

    int[][] left(int size) {
        int[] mat = new int[size];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            int[] val = new int[size];
            Arrays.fill(val, n);
            mat[n] = val;
        });
        return mat;
    }

    int[][] right(int size) {
        int[] mat = new int[size];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            mat[n] = IntStream.range(1, size+1).toArray();
        });
        return mat;
    }

}
