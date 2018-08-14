package example

import java.nio.ByteBuffer
import java.nio.file.{Files, Paths, StandardOpenOption}
import java.nio.charset.Charset;
import java.util.Arrays;

import scala.util.{Try, Success, Failure}

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
        val s = new String(Arrays.copyOf(buffer.array(), size), Charset.forName("utf-8"))
        println("ss:" + s)

        val (ch, wd, lf) = countup(s)
        println("ch:" + ch + ", w:"+ wd + ", lf:" + lf)

      } while(size == alocSize)
    }
  }

  def countup(ss: String): (Int, Int, Int) /* ch, word, line */ = {
    def eqC(c: Char, e: Char): Int = {
      return if (c == e) 1 else 0
    }
    def wdC(c: Char, e1: Char, e2: Char): Int = {
      if (c == e1) {
        return 1
      }
      return eqC(c, e2)
    }
    def rd(x: (Int, Int, Int), y: (Int, Int, Int)): (Int, Int, Int) = {
      return (x._1 + y._1, x._2 + y._2, x._3 + y._3)
    }
    def chP(c: Char): Int = {
      //println(">" + c)
      return 1
    }
    println("SS: " + ss.length() + ", " + ss.getBytes.length)
    return ss
      .map(c => (chP(c), wdC(c, ' ', '\n'), eqC(c, '\n')))
      .reduceLeft(rd)
  }
}
