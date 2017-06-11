package controllers

import javax.inject.Inject

import daos.ProductsDAO
import daos.CategoriesDAO
import daos.BasketDAO

import models.ProductsREST
import models.CategoriesREST
import models.BasketREST

import models.Products
import models.Categories
import models.Basket

import play.api.libs.json.Json
import play.api.mvc._
import play.api.libs.concurrent.Execution.Implicits.defaultContext

class Application @Inject() (productsDAO: ProductsDAO, categoriesDAO: CategoriesDAO, basketDAO: BasketDAO) extends Controller {

  // list of all products
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

  def addToBasket = Action { implicit request =>
    var json:BasketREST = request.body.asJson.get.as[BasketREST]
    var basket = Basket(id = 0, userId = json.userId, prodId = json.prodId, comments = json.comments)
    basketDAO.insert(basket)
    Ok(request.body.asJson.get)
  }

  def removeFromBasket(id: Long) = Action { implicit request =>
    println("request=" + request)
    basketDAO.remove(id)
    Ok("200")
  }

  // list of categories
  def categories = Action.async { implicit  request =>
    categoriesDAO.all map {
      categories => Ok(Json.toJson(categories))
    }
  }

  // data connected with one specific product
  def product(id: Int) = Action.async { implicit  request =>
    productsDAO.one(id) map {
      products => Ok(Json.toJson(products))
    }
  }

  // list of all products from a specified category
  def category(id: Int) = Action.async { implicit  request =>
    productsDAO.fromCategory(id) map {
      products => Ok(Json.toJson(products))
    }
  }

  // list of all products from a basket of specified user
  def basket(id: String) = Action.async { implicit  request =>
    println("Basket for id=" + id)
    basketDAO.forUser(id) map {
      products => Ok(Json.toJson(products))
    }
  }

  }
