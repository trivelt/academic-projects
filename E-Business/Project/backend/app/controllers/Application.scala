package controllers

import javax.inject.Inject

import daos.ProductsDAO
import daos.CategoriesDAO

import models.ProductsREST
import models.CategoriesREST

import models.Products
import models.Categories

import play.api.libs.json.Json
import play.api.mvc._
import play.api.libs.concurrent.Execution.Implicits.defaultContext

class Application @Inject() (productsDAO: ProductsDAO, categoriesDAO: CategoriesDAO) extends Controller {

  def index = Action.async { implicit  request =>
    productsDAO.all map {
      products => Ok(Json.toJson(products))
    }
  }

  def newproduct = Action { implicit request =>
    var json:ProductsREST = request.body.asJson.get.as[ProductsREST]
    var product = Products(prodId = 0, tytul = json.tytul, opis = json.opis, catId = json.catId)
    productsDAO.insert(product)
    Ok(request.body.asJson.get)
  }

  def categories = Action.async { implicit  request =>
    categoriesDAO.all map {
      categories => Ok(Json.toJson(categories))
    }
  }
}
