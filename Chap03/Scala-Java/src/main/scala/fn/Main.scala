package fn


object Exec extends App {
  UNameFunc.run()

  new Lambda().exec()

}


object HiExec extends App {
  HighOrderFunc.run()

  new HighOrder().exec();
}
