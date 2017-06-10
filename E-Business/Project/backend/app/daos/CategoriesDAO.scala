package daos

import javax.inject.Inject

import models.{Categories, CategoriesREST}
import play.api.db.slick.{DatabaseConfigProvider, HasDatabaseConfigProvider}
import slick.driver.JdbcProfile
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.{ExecutionContext, Future}

/**
  * Created by kprzystalski on 23/04/17.
  */

class CategoriesDAO @Inject()(protected val dbConfigProvider: DatabaseConfigProvider)
  extends HasDatabaseConfigProvider[JdbcProfile] {

  import driver.api._

  val Categories = TableQuery[CategoriesTable]

  def all(implicit ec: ExecutionContext): Future[List[CategoriesREST]] = {
    val query =  Categories
    val results = query.result
    val futureCategories = db.run(results)
    futureCategories.map(
      _.map {
        a => CategoriesREST(tytul = a.tytul, catId = a.catId)
      }.toList)
  }

  def insert(category: Categories): Future[Unit] = db.run(Categories += category).map { _ => () }


  class CategoriesTable(tag: Tag) extends Table[Categories](tag, "Categories") {
    def catId = column[Long]("catId",O.AutoInc, O.AutoInc)
    def tytul = column[String]("tytul")
    def * = (catId, tytul) <> (models.Categories.tupled, models.Categories.unapply)
  }

}
