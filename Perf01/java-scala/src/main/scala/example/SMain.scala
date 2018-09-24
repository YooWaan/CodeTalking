package example

import java.io.InputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.concurrent.Callable;
import java.util.concurrent.{Executors, ExecutorService, Future};

//import com.sun.net.httpserver.HttpHandler;
//import com.sun.net.httpserver.HttpServer;

import scala.concurrent.ExecutionContext;

object SMain extends App {
  if (args.length == 1) {
    HttpApp.serve(new WCHttp())
  } else if (args.length == 2) {
    Mat.calc(args(0).toInt, args(1).toInt)
  } else {
    WC.run(args(0).toInt, args.drop(1))
  }
}

class WCHttp extends WordWebApp {

  @throws(classOf[IOException])
  @throws(classOf[InterruptedException])
  override def count(in: InputStream, contentLength: Int) : Array[Byte] = {
    val es =ExecutionContext.fromExecutorService(Executors.newFixedThreadPool(4))
    val alocSize = 4048
    val buffer = ByteBuffer.allocate(alocSize).array()

    var futures: List[Future[(Int,Int,Int)]] = List()
    var size = 0
    var readSz = 0

    try {
      do {
        size = in.read(buffer)
        val s = new String(Arrays.copyOf(buffer, size), Charset.forName("utf-8"))
        val c = new Callable[(Int,Int,Int)]() {
          def call(): (Int,Int,Int) = {
            return countup(s)
          }
        }
        readSz += size
        futures =  es.submit(c) :: futures
      } while(readSz < contentLength)

    } finally {
      in.close();
      es.shutdown();
    }

    val result = futures.map(_.get()).reduce((a,b) => (a._1 + b._1, a._2 + b._1, a._3 + b._3))
    val ss = "" + result._1 + "\t" + result._2 + "\t" + result._3
    return ss.getBytes();
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
      .map(c => (1, wdC(c, ' ', '\n'), eqC(c, '\n')))
      .reduce(rd)
  }

}
