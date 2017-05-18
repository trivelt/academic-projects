package demo

/**
  * Created by mmichale
  */

class CloneableProduct() {
  override def clone(): CloneableProduct = new CloneableProduct()
}

class ProductPrototype(var name: String) extends CloneableProduct() {
  var price: Int = 1
  var description: String = "No description yet"
  var views: Int = 0
  var inStock: Int = 0

  override def clone(): CloneableProduct = {
    var p: CloneableProduct = new ProductPrototype(name)
    p.asInstanceOf[ProductPrototype].price = price
    p.asInstanceOf[ProductPrototype].description = description
    p.asInstanceOf[ProductPrototype].views = views
    p.asInstanceOf[ProductPrototype].inStock = inStock
    return p
  }

  def info(): String = "Product " + name + "\nPrice: " + price + " PLN\nDescription: " + description +
    "\nViews: " + views + "\nIn stock: " + inStock

  def setPrice(p_price: Int) {
    if(p_price > 0 ) {
      this.price = p_price
    } else {
      println("ERROR: Wrong price " + p_price)
    }
  }

  def view(): Unit = {
    views += 1
  }

  def buy(): Unit = {
    inStock -= 1
  }
}

object PrototypeDemo {
  def main(args: Array[String]): Unit = {

    var originalProduct = new ProductPrototype("walkman")
    originalProduct.inStock = 10
    originalProduct.setPrice(150)
    var i = 0
    for(i <- 0 to 19) {
      originalProduct.view()
    }

    var copyOfProduct = originalProduct.clone().asInstanceOf[ProductPrototype]
    copyOfProduct.view()
    copyOfProduct.buy()
    println(copyOfProduct.info())
  }
}