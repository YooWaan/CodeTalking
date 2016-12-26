package fn;

import java.util.List;
import java.util.stream.IntStream;
import java.util.stream.Collectors;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.function.Consumer;
import java.util.function.BiConsumer;
import java.util.function.IntPredicate;
import java.util.function.IntUnaryOperator;
import java.util.function.IntBinaryOperator;

public class HighOrder {

    public void exec() {

        Consumer<String> pln = System.out::println;
        BiConsumer<String,IntStream> p = (s,a) -> {
            System.out.println(s + a.mapToObj(Integer::valueOf).collect(Collectors.toList()));
        };

        Supplier<IntStream> data = () -> {
            return IntStream.range(0,11);
        };

        pln.accept("---- Java High Order ----");
        p.accept("data->", data.get());

        // functions
        IntPredicate   filter = (a) -> a % 2 == 0;
        IntUnaryOperator  map = (a) -> 2 * a;
        IntBinaryOperator sum = (a,b) -> a + b;

        // argument
        p.accept("filter->", data.get().filter(filter));
        p.accept("filter-> map->", data.get().filter(filter).map(map));
        pln.accept("filter-> map-> reduce->" + data.get().filter(filter).map(map).reduce(sum));

        // currying

        Supplier<Function<IntStream, Integer>> currying = () -> {
            return (a) -> a.filter(filter).map(map).reduce(sum).getAsInt();
        };

        Function<IntStream, Integer> sumFn = currying.get();
        pln.accept("currying->" + sumFn.apply(data.get()));

    }
}
