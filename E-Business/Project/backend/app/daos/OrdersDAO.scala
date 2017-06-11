package daos

import javax.inject.Inject

import models.{Orders, OrdersREST}
import play.api.db.slick.{DatabaseConfigProvider, HasDatabaseConfigProvider}
import slick.driver.JdbcProfile
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.{ExecutionContext, Future}

/**
  * Created by mmichale
  */

class OrdersDAO @Inject()(protected val dbConfigProvider: DatabaseConfigProvider)
  extends HasDatabaseConfigProvider[JdbcProfile] {

  import driver.api._

  val Orders = TableQuery[OrdersTable]

  def insert(orders: Orders): Future[Unit] = db.run(Orders += orders).map { _ => () }

  class OrdersTable(tag: Tag) extends Table[Orders](tag, "Orders") {
    def id = column[Long]("id",O.AutoInc, O.AutoInc)
    def userId = column[String]("userId")
    def products = column[String]("products")
    def shippmentMethod = column[String]("shippmentMethod")
    def paymentMethod = column[String]("paymentMethod")
    def date = column[String]("date")
    def address = column[String]("address")
    def price = column[Long]("price")
    def * = (id, userId, products, shippmentMethod, paymentMethod, date, address, price) <> (models.Orders.tupled, models.Orders.unapply)
  }

}






//case class Orders(id: Long, userId: String, products: String, shippmentMethod: String,
//                  paymentMethod: String, date: String, address: String, price: Long);