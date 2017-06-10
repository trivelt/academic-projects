package daos

import javax.inject.Inject

import models.{Products, ProductsREST}
import play.api.db.slick.{DatabaseConfigProvider, HasDatabaseConfigProvider}
import slick.driver.JdbcProfile
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.{ExecutionContext, Future}

/**
  * Created by kprzystalski on 23/04/17.
  */

class ProductsDAO @Inject()(protected val dbConfigProvider: DatabaseConfigProvider)
  extends HasDatabaseConfigProvider[JdbcProfile] {

  import driver.api._

  val Products = TableQuery[ProductsTable]

  def all(implicit ec: ExecutionContext): Future[List[ProductsREST]] = {
    val query =  Products
    val results = query.result
    val futureProducts = db.run(results)
    futureProducts.map(
      _.map {
        a => ProductsREST(opis = a.opis, tytul = a.tytul)
      }.toList)
  }

  def insert(product: Products): Future[Unit] = db.run(Products += product).map { _ => () }


  class ProductsTable(tag: Tag) extends Table[Products](tag, "Products") {
    def prodId = column[Long]("prodId",O.AutoInc, O.AutoInc)
    def tytul = column[String]("tytul")
    def opis = column[String]("opis")
    def * = (prodId, tytul, opis) <> (models.Products.tupled, models.Products.unapply)
  }

}
