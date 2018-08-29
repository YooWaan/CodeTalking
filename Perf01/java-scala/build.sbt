import Dependencies._

assemblyJarName in assembly := "java-scala.jar"

lazy val root = (project in file(".")).
  settings(
    inThisBuild(List(
      organization := "com.example",
      scalaVersion := "2.12.4",
      version      := "0.1.0-SNAPSHOT"
    )),
    name := "wc-ja",
    libraryDependencies += scalaTest % Test
  )
