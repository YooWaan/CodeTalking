package example

import java.net.InetSocketAddress;

import com.sun.net.httpserver._

object SMain extends App {
  if (args.length == 1) {
    println("http")
  } else if (args.length == 2) {
    Mat.calc(args(0).toInt, args(1).toInt)
  } else {
    WC.run(args(0).toInt, args.drop(1))
    //WC.count("../README.md")
  }
}

object Http {

  def serve() {
    val server = HttpServer.create(new InetSocketAddress(8080), 0)
    server.createContext("/jwc", new WordWebApp())
    server.start()
  }
}
