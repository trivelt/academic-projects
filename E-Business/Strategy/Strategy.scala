package demo

/**
  * Created by mmichale
  */

abstract class Parser {
  def parse(filepath: String)
}

class CSVParser extends Parser {
  def parse(filepath: String): Unit = {
    println("Using CSVParser::parse()")
  }
}

class JsonParser extends Parser {
  def parse(filepath: String): Unit = {
    println("Using JsonParser::parse()")
  }
}

object StrategyDemo {
  var parser: Parser = null
  var filepath: String = ""

  object Strategy extends Enumeration {
    type Strategy = Value
    val CVS, Json = Value
  }
  import Strategy._

  def setStrategy(strategy: Strategy): Unit = {
    if(strategy == CVS) {
      parser = new CSVParser()
    } else if(strategy == Json) {
      parser = new JsonParser()
    }
  }

  def parse(): Unit = {
    parser.parse(filepath)
  }

  def main(args: Array[String]): Unit = {
    println("Strategy design pattern")
    if(args.length != 1) {
      println("Invalid parameters. Please run app with exactly one argument")
      System.exit(1)
    }

    filepath = args(0)
    if(filepath.endsWith(".cvs")) {
      setStrategy(CVS)
    } else if(filepath.endsWith(".json")) {
      setStrategy(Json)
    } else {
      println("Invalid file format")
      System.exit(1)
    }

    parse()
  }
}