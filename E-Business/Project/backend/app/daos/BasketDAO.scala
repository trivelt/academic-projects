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
    val futureProduct = db.run(Basket.filter(_.userId === userId).result)
    futureProduct.map(
      _.map {
        a => BasketREST(userId = a.userId, prodId = a.prodId, comments = a.comments)
      }.toList)
  }

  def insert(basket: Basket): Future[Unit] = db.run(Basket += basket).map { _ => () }

  class BasketTable(tag: Tag) extends Table[Basket](tag, "Basket") {
    def id = column[Long]("id",O.AutoInc, O.AutoInc)
    def userId = column[String]("userId")
    def prodId = column[Long]("prodId")
    def comments = column[String]("comments")
    def * = (id, userId, prodId, comments) <> (models.Basket.tupled, models.Basket.unapply)
  }

}
