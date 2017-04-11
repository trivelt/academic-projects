
import scala.io.Source


/**
  * Created by mmichale
  */


trait Reader  {
  def read(): String = ""
}


abstract class ReaderDecorator(decoratedReader: Reader) extends Reader {
  override def read(): String = decoratedReader.read()
}

class InputReader extends Reader {
  override  def read(): String = {
    var text: String = ""
    Source.stdin.getLines().foreach {
      case line => line match {
        case "EXIT" =>
          return text
        case l =>
          text += line
      }
    }
    return text
  }
}

class FileReader (filepath: String) extends Reader {
  override  def read(): String = scala.io.Source.fromFile(filepath).mkString
}

class WhitespaceCleanReader (decoratedReader: Reader) extends ReaderDecorator(decoratedReader) {
  override  def read(): String = decoratedReader.read().replaceAll("\\s", "")
}

class UppercaseReader (decoratedReader: Reader) extends ReaderDecorator(decoratedReader) {
  override  def read(): String = decoratedReader.read().toUpperCase
}



object DecoratorEx {
  def main(args: Array[String]): Unit = {
    //var testReader: Reader = new InputReader
    var testReader: Reader = new FileReader("test.txt")
    testReader = new WhitespaceCleanReader(testReader)
    testReader = new UppercaseReader(testReader)
   println(testReader.read())
  }
}
