package fn


object HighOrderFunc {

  def filter_fn(a:Int) : Boolean = {
    return a % 2 == 0
  }

  def map_fn(a:Int) : Int = {
    return 2*a
  }

  def sum_fn(a:Int, b:Int) : Int = {
    return a+b
  }

  def currying() : (List[Int]) => Int = {
    def sum(dat:List[Int]) : Int = {
      return dat.filter(filter_fn).map(map_fn).reduce(sum_fn)
    }
    return sum
  }


  def run() {

    println("--- High order Scala ---")

    val data = Range(0,11).toList

    // argument
//    println("data ->" + data)
    println("filter->" + data.filter(filter_fn))
    println("filter-> map->" + data.filter(filter_fn).map(map_fn))
    println("filter-> map-> reduce->" + data.filter(filter_fn).map(map_fn).reduce(sum_fn))

    // currying
    val sumFn = currying()
    println("currying->" + sumFn(data))
  }

}
