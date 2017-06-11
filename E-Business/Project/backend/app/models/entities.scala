package models

import java.sql.Timestamp

import play.api.libs.json.Format

/**
  * Created by kprzystalski on 23/04/17.
  */

case class Products(prodId: Long, tytul: String, opis: String, catId: Long)
case class Categories(catId: Long, tytul: String)
case class Basket(id: Long, userId: String, prodId: Long, comments: String)
case class Orders(id: Long, userId: String, products: String, shippmentMethod: String,
                  paymentMethod: String, date: String, address: String, price: Long)