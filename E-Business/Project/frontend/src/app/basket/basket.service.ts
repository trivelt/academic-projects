import { Injectable } from '@angular/core';
import {Http, Headers, RequestOptions, URLSearchParams} from "@angular/http";
import {Basket} from "./basket";
import 'rxjs/add/operator/map';

@Injectable()
export class BasketService {

  constructor(private http: Http) { }

  getBasket() {
    console.log("Get basket");
    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    let params: URLSearchParams = new URLSearchParams();
    params.set('id', "fb:1234"); //TODO: get current user id (oauth2)

    const options = new RequestOptions({headers: headers, search: params});

    return this.http.get('http://localhost:9000/basket', options)
      .map(response => <Basket[]>response.json());
  }

}
