package models

import play.api.libs.json.Json

/**
  * Created by kprzystalski on 23/04/17.
  */
case class ProductsREST(tytul: String, opis: String, catId: Long, prodId: Long)
case class CategoriesREST(tytul: String, catId: Long)
case class BasketREST(id: Long, userId: String, prodId: Long, comments: String)

object ProductsREST {
  implicit val productsFormat = Json.format[ProductsREST]
}

object CategoriesREST {
  implicit val categoriesFormat = Json.format[CategoriesREST]
}

object BasketREST {
  implicit val basketFormat = Json.format[BasketREST]
}