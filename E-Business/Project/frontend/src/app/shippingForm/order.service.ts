import { Injectable } from '@angular/core';
import {Http, Headers, RequestOptions} from "@angular/http";
import {Order} from "./order";
import 'rxjs/add/operator/map';

@Injectable()
export class OrderService {

  constructor(private http: Http) {}

  makeOrder(userId: string, products: string, shippmentMethod: string,
            paymentMethod: string, address: string, price: number) {
    console.log("makeOrder called");

    const serializedOrder = JSON.stringify({
      "id": 0,
      "userId": userId,
      "products": products,
      "shippmentMethod": shippmentMethod,
      "paymentMethod": paymentMethod,
      "date": "15 czerwca",
      "address": address,
      "price": Number(price)
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
