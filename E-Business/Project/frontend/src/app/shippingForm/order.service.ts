import { Injectable } from '@angular/core';
import {Http, Headers, RequestOptions} from "@angular/http";
import {Order} from "./order";
import 'rxjs/add/operator/map';
import {LoginService} from '../login/login.service';
import {BasketService} from '../basket/basket.service';

@Injectable()
export class OrderService {

  constructor(private loginService: LoginService, private http: Http) {}

  makeOrder() {
    console.log("makeOrder called");
    var profile = this.loginService.userProfile;
    var userId: string = profile.sub;

    const serializedOrder = JSON.stringify({
      "id": 0,
      "userId": userId,
      "products": "cos, cos2",
      "shippmentMethod": "paczkomat",
      "paymentMethod": "karta",
      "date": "15 czerwca",
      "address": "Krakow",
      "price": 123
    })

    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    const options = new RequestOptions({headers: headers});

    this.http.post('http://localhost:9000/order', serializedOrder, options)
      .subscribe(
        data => console.log('product added to basket', data),
        error => console.error('adding to basked error', error)
      );

  }
}
