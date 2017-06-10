package models

import play.api.libs.json.Json

/**
  * Created by kprzystalski on 23/04/17.
  */
case class ProductsREST(tytul: String, opis: String)
case class CategoriesREST(tytul: String)

object ProductsREST {
  implicit val productsFormat = Json.format[ProductsREST]
}

object CategoriesREST {
  implicit val categoriesFormat = Json.format[CategoriesREST]
}