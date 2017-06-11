package daos

import javax.inject.Inject

import models.{Basket, BasketREST}
import play.api.db.slick.{DatabaseConfigProvider, HasDatabaseConfigProvider}
import slick.driver.JdbcProfile
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.{ExecutionContext, Future}

/**
  * Created by mmichale
  */

class BasketDAO @Inject()(protected val dbConfigProvider: DatabaseConfigProvider)
  extends HasDatabaseConfigProvider[JdbcProfile] {

  import driver.api._

  val Basket = TableQuery[BasketTable]

  def forUser(userId: String): Future[List[BasketREST]] = {
    val futureBasket = db.run(Basket.filter(_.userId === userId).result)
    futureBasket.map(
      _.map {
        a => BasketREST(id = a.id, userId = a.userId, prodId = a.prodId, comments = a.comments, price = a.price)
      }.toList)
  }

  def insert(basket: Basket): Future[Unit] = db.run(Basket += basket).map { _ => () }

  def remove(id: Long): Future[Unit] = db.run(Basket.filter(_.id === id).delete).map { _ => () }


  class BasketTable(tag: Tag) extends Table[Basket](tag, "Basket") {
    def id = column[Long]("id",O.AutoInc, O.AutoInc)
    def userId = column[String]("userId")
    def prodId = column[Long]("prodId")
    def comments = column[String]("comments")
    def price = column[Long]("price")
    def * = (id, userId, prodId, comments, price) <> (models.Basket.tupled, models.Basket.unapply)
  }

}
