package example;

import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.function.Function;

public class Matrix {

    public static void main(String[] args) {
        if (args.length == 3) {
            new Matrix().calc(Integer.valueOf(args[1]).intValue(), Integer.valueOf(args[2]).intValue());
        }
    }

    public void calc(int start, int end) {
        long cnt = IntStream.range(start, end)
        .mpa(sz -> {
            int[] ans = mul(left(sz), right(sz));
            return ans.length;
        }).count();
        //System.out.println("Time:" + (System.nanoTime() - start) / 1000 + " msec");
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
        int[][] mat = new int[size][];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            int[] val = new int[size];
            Arrays.fill(val, n);
            mat[n] = val;
        });
        return mat;
    }

    int[][] right(int size) {
        int[][] mat = new int[size][];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            mat[n] = IntStream.range(1, size+1).toArray();
        });
        return mat;
    }

}
