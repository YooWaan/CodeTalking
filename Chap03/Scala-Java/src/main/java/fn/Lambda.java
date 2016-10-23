package fn;

import java.util.function.Supplier;
import java.util.function.Consumer;
import java.util.function.BiFunction;

public class Lambda {

    Supplier<Integer> getClosure() {
        final int[] cnt = new int[]{0};
        Supplier<Integer> inc = () -> {
            cnt[0]++;
            return cnt[0];
        };
        return inc;
    }

    public void exec() {
        Consumer<String> prt = System.out::println;
        prt.accept("--- Java ---");

        Integer n = ((BiFunction<Integer,Integer,Integer>)(x,y) -> { return x+y; }).apply(1,2);
        prt.accept("calc -> " + n);

        BiFunction<Integer,Integer,Integer> f = (x,y) -> { return x+y; };
        prt.accept("func -> " + f.apply(1,2));

        Supplier<Integer> c = getClosure();
        prt.accept("cnt 1 -> " + c.get());
        prt.accept("cnt 2 -> " + c.get());
        prt.accept("cnt 3 -> " + c.get());
        prt.accept("cnt 4 -> " + c.get());
        prt.accept("cnt 5 -> " + c.get());
        
    }

}
