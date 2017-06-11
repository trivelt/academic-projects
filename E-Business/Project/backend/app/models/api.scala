package models

import play.api.libs.json.Json

/**
  * Created by kprzystalski on 23/04/17.
  */
case class ProductsREST(tytul: String, opis: String, catId: Long, prodId: Long)
case class CategoriesREST(tytul: String, catId: Long)
case class BasketREST(id: Long, userId: String, prodId: Long, comments: String)
case class OrdersREST(id: Long, userId: String, products: String, shippmentMethod: String,
                  paymentMethod: String, date: String, address: String, price: Long)

object ProductsREST {
  implicit val productsFormat = Json.format[ProductsREST]
}

object CategoriesREST {
  implicit val categoriesFormat = Json.format[CategoriesREST]
}

object BasketREST {
  implicit val basketFormat = Json.format[BasketREST]
}

object OrdersREST {
  implicit val ordersFormat = Json.format[OrdersREST]
}