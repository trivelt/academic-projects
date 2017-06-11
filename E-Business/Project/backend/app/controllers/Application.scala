package controllers

import javax.inject.Inject

import daos.ProductsDAO
import daos.CategoriesDAO
import daos.BasketDAO
import daos.OrdersDAO

import models.ProductsREST
import models.CategoriesREST
import models.BasketREST
import models.OrdersREST

import models.Products
import models.Categories
import models.Basket
import models.Orders

import play.api.libs.json.Json
import play.api.mvc._
import play.api.libs.concurrent.Execution.Implicits.defaultContext

class Application @Inject() (productsDAO: ProductsDAO, categoriesDAO: CategoriesDAO, basketDAO: BasketDAO, ordersDAO: OrdersDAO) extends Controller {

  // list of all products
  def index = Action.async { implicit  request =>
    productsDAO.all map {
      products => Ok(Json.toJson(products))
    }
  }

  def newproduct = Action { implicit request =>
    var json:ProductsREST = request.body.asJson.get.as[ProductsREST]
    var product = Products(prodId = 0, tytul = json.tytul, opis = json.opis, catId = json.catId, price = json.price)
    productsDAO.insert(product)
    Ok(request.body.asJson.get)
  }

  // add product to basket
  def addToBasket = Action { implicit request =>
    var json:BasketREST = request.body.asJson.get.as[BasketREST]
    var basket = Basket(id = 0, userId = json.userId, prodId = json.prodId, comments = json.comments)
    basketDAO.insert(basket)
    Ok(request.body.asJson.get)
  }

  // remove product from basket
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

  // make an order
  def order() = Action { implicit request =>
    var json:OrdersREST = request.body.asJson.get.as[OrdersREST]
    var order = Orders(id = 0, userId = json.userId, products = json.products, shippmentMethod = json.shippmentMethod,
                       paymentMethod = json.paymentMethod, date = json.date, address =  json.address, price = json.price)
    ordersDAO.insert(order)
    Ok(request.body.asJson.get)
  }

  }
