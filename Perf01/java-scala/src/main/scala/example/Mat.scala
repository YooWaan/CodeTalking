package example

object Mat {

  def calc(): Unit = {
    //val ans = Array.range(1,1000).map(x => mul(matrix(x), mat(x))).toList
    val ans = scala.collection.parallel.mutable.ParArray
      .range(1,1000).map(x => mul(matrix(x), mat(x))).toList
    println(ans.length)
  }

  def matrix(size: Int): Array[Array[Int]] = {
    Array.range(1, size).map(a => Array.range(1, size))
  }

  def mat(size: Int): Array[Array[Int]] = {
    Array.range(1, size).map(x => Array.fill(size-1){x})
  }

  def mul(m1: Array[Array[Int]], m2: Array[Array[Int]]): Array[Int] = {
    val mt = m2.transpose
    m1.zipWithIndex.map { case (v, i) => v zip mt(i) map Function.tupled(_*_) reduceLeft(_+_)}
  }

  def show(m: Array[Array[Int]]): Unit = {
    m.foreach(a => println("[" + a.mkString(",") + "]"))
  }

}
