package example

import java.lang.AutoCloseable
import java.nio.ByteBuffer
import java.nio.file.{Files, Paths, StandardOpenOption}
import java.nio.charset.Charset;
import java.net.InetSocketAddress;

import com.sun.net.httpserver._

import scala.util.{Try, Success, Failure}


object Hello extends App {
  WC.count("../README.md")
  //Matrix.calc()
}

object Http {

  def serve() {
    val server = HttpServer.create(new InetSocketAddress(8080), 0)
    server.createContext("/jwc", new WordCounter())
    server.start()
  }
}


object Matrix {

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


case class Count(Page :Long, Bytes :Long, Words :Long)

object WC {

  def tryResource[A <: AutoCloseable, B](rc: A)(clean: A => Unit)(fun: A => B): Try[B] = {
    try {
      Success(fun(rc))
    } catch {
      case e: Exception => Failure(e)
    } finally {
      try {
        if (rc != null) {
          clean(rc)
        }
      } catch {
        case e: Exception => e.printStackTrace()
      }
    }
  }

  def count(filename: String): Unit = {
    val alocSize = 4048
    val path = Paths.get(filename)

    println(filename + " ===> "  + path)

    val buffer = ByteBuffer.allocate(alocSize)
    tryResource(Files.newByteChannel(path, StandardOpenOption.READ))(_.close()) { rc =>
      var size = 0
      do {
        size = rc.read(buffer)

        val s = new String(buffer.array(), Charset.forName("utf-8"))
        println("Sz:" + size + "-----")
        println(s)


        val (ch, wd, lf) = countup(s)
        println("ch:" + ch + ", w:"+ wd + ", lf:" + lf)

      } while(size == alocSize)
    }
  }

  def countup(ss: String): (Int, Int, Int) /* ch, word, line */ = {
    def eqC(c: Char, e: Char): Int = {
      return if (c == e) 1 else 0
    }
    def rd(x: (Int, Int, Int), y: (Int, Int, Int)): (Int, Int, Int) = {
      return (x._1 + y._1, x._2 + y._2, x._3 + y._3)
    }
    return ss.map(c => (1, eqC(c, ' '), eqC(c, '\n')))
      .reduceLeft(rd)
  }
}
