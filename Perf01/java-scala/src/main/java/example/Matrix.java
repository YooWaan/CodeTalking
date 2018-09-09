package example;

import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Matrix {

    public static void main(String[] args) {
        if (args.length == 2) {
            new Matrix().calc(Integer.valueOf(args[0]).intValue(), Integer.valueOf(args[1]).intValue());
        } else {
            System.out.println("args:" + args.length + "cmd start end\ncmd port\ncmd num files");
        }
    }

    public void calc(int start, int end) {
        long cnt = IntStream.range(start, end+1).parallel()
        .map(sz -> {
            int[][] ans = mul(left(sz), right(sz));
            //print(ans);
            return ans.length;
        }).count();
        //System.out.println("Time:" + (System.nanoTime() - start) / 1000 + " msec");
    }

    void print(int[][] v) {
        System.out.println("--------------");
        for (int[] row : v) {
            System.out.println('[' + Arrays.stream(row)
                               .mapToObj(i -> Integer.valueOf(i).toString())
                               .collect(Collectors.joining(","))+']');
        }
        System.out.println("--------------");
    }

    int[][] mul(int[][] left, int[][] right) {
        int sz = left.length;
        int[][] ans = new int[sz][sz];
        for (int ii = 0; ii < sz ;ii++) {
            int[] row = new int[sz];
            for (int nn = 0; nn < sz ;nn++) {
                for (int mm = 0;mm < sz; mm++) {
                    row[nn] += left[ii][mm] * right[mm][nn];
                }
            }
            ans[ii] = row;
        }
        return ans;
    }

    int[][] left(int size) {
        int[][] mat = new int[size][];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            int[] val = new int[size];
            Arrays.fill(val, n);
            mat[n-1] = val;
        });
        return mat;
    }

    int[][] right(int size) {
        int[][] mat = new int[size][];
        IntStream.range(1, size + 1)
        .forEach(n -> {
            mat[n-1] = IntStream.range(1, size+1).toArray();
        });
        return mat;
    }

}
