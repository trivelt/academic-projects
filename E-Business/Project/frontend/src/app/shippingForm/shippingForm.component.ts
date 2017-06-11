import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";
import {Order} from "./order";
import {OrderService} from "./order.service";
import {BasketService} from '../basket/basket.service';
import {LoginService} from '../login/login.service';

@Component({
  selector: 'shipping-form',
  templateUrl: './shippingForm.component.html',
})
export class ShippingFormComponent implements OnInit {

  productForm: FormGroup;

  shippmentMethods = ["Poczta Polska - przesylka ekonomiczna",
                      "Poczta Polska - przesylka priorytetowa",
                      "Kurier Pocztex24",
                      "Paczkomat",
                      "Kurier DHL"];

  paymentMethods = ["Za pobraniem",
                    "Przelew tradycyjny",
                    "Przelewy24.pl",
                    "Karta platnicza",
                    "PayPal",
                    "Bitcoin"]

  model = new Order();
  step = 1

  constructor(private loginService: LoginService,
              private basketService: BasketService,
              private orderService: OrderService,
              private route: ActivatedRoute) { }

  ngOnInit() {
      this.model.paymentMethod = this.paymentMethods[0];
      this.model.shippmentMethod = this.shippmentMethods[1];
    // var prodId = this.route.snapshot.params['id'];
  }

  showSummary() {
    console.log("showSummary clicked, address=" + this.model.address);
    this.step = 2;
  }

  sendOrder() {
    console.log("Send order clicked");
    var profile = this.loginService.userProfile;
    var userId: string = profile.sub;

    var products = "abcd efg";
    var price = 153;
    this.orderService.makeOrder(userId,
                                products,
                                this.model.shippmentMethod,
                                this.model.paymentMethod,
                                this.model.address,
                                price);
    this.step = 3;
  }


}
