

def divide(a: Int, b: Int): Either[String, Int] = {
  if (b <= 0) Left("Invalid Number")
  else Right(a/b)
}

def div_example1(): Unit = {
  divide(10, 2) match {
    case Left(err) => println(s"Failed: $err")
    case Right(result) => println(s"Num: $result")
  }
}

def div_example2(): Unit = {
  var num = for {
    a <- divide(10, 2)
    b <- divide(a, 2)
  } yield b

  println(s"Num: $num")

  num = for {
    a <- divide(10, 2)
    b <- divide(a, 0)
  } yield b
  println(s"Num: $num")
}

div_example1()
div_example2()
