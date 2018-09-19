package example

import java.nio.ByteBuffer
import java.nio.file.{Files, Paths, StandardOpenOption}
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.concurrent.Callable;
import java.util.concurrent.{Executors, ExecutorService, Future};

import scala.util.{Try, Success, Failure};
import scala.concurrent.ExecutionContext;

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

  def run(times: Int, files: Array[String]): Unit = {
    //println("times===>" + times + ", " + files)
    Array.range(0, times).map(i => {
      val idx = i % files.length
      files(idx)
    }).foreach(fpath => {
      val cnt = count(fpath)
      System.err.println("" + cnt._1 + "\t"+ cnt._2 + "\t" + cnt._3)
    })
  }

  def count(filename: String): (Int,Int,Int) = {
    val alocSize = 4048
    val path = Paths.get(filename)
    val buffer = ByteBuffer.allocate(alocSize)
    var futures: List[Future[(Int,Int,Int)]] = List()
    //val es =ExecutionContext.fromExecutorService(Executors.newCachedThreadPool())
    val es =ExecutionContext.fromExecutorService(Executors.newFixedThreadPool(12))

    try {
      tryResource(Files.newByteChannel(path, StandardOpenOption.READ))(_.close()) { rc =>
        var size = 0
        do {
          size = rc.read(buffer)
          val s = new String(Arrays.copyOf(buffer.array(), size), Charset.forName("utf-8"))
          buffer.clear()
          val c = new Callable[(Int,Int,Int)]() {
            def call(): (Int,Int,Int) = {
              return countup(s)
            }
          }
          futures =  es.submit(c) :: futures
        } while(size == alocSize)
      }
    } finally {
      es.shutdown()
    }

    futures.map(_.get()).reduce((a,b) => (a._1 + b._1, a._2 + b._1, a._3 + b._3))
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
    return ss
      .map(c => (chP(c), wdC(c, ' ', '\n'), eqC(c, '\n')))
      .reduce(rd)
  }
}
