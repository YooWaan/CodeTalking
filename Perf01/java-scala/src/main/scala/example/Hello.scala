package example

import java.net.InetSocketAddress;

import com.sun.net.httpserver._

object Hello extends App {
  WC.count("../README.md")
  //Matrix.calc()
}

object Http {

  def serve() {
    val server = HttpServer.create(new InetSocketAddress(8080), 0)
    server.createContext("/jwc", new WordWebApp())
    server.start()
  }
}
