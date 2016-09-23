package fn



object UNameFunc {

  def getClosure() :(() => Int) = {
    var cnt: Int = 0
    def inc() : Int = {
      cnt += 1
      return cnt
    }
    return inc
  }

  def run() {
    val n = ((x:Int, y:Int) => {x + y})(3,2)
    println( "calc -> " + n )

    val f = (x:Int, y:Int) => {x + y}
    println( "func -> " + f(1,2) )

    val c = getClosure()
    println( "cnt 1 -> " + c())
    println( "cnt 2 -> " + c())
    println( "cnt 3 -> " + c())
    println( "cnt 4 -> " + c())
    println( "cnt 5 -> " + c())

  }

}




