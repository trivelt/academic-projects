import { Injectable } from '@angular/core';
import {Http, Headers, RequestOptions, URLSearchParams} from "@angular/http";
import {Basket} from "./basket";
import { LoginService } from '../login/login.service';
import 'rxjs/add/operator/map';

@Injectable()
export class BasketService {

  profile: any;

  constructor(private loginService: LoginService, private http: Http) { }

  getBasket() {
    console.log("Get basket");

    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');


    this.profile = this.loginService.userProfile;
    var userId: string = this.profile.sub; //TODO: check if sub exists
    console.log("UserID=" + userId);

    let params: URLSearchParams = new URLSearchParams();
    params.set('id', userId);

    const options = new RequestOptions({headers: headers, search: params});

    return this.http.get('http://localhost:9000/basket', options)
      .map(response => <Basket[]>response.json());
  }

  removeBasket(id: number) {
    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    const options = new RequestOptions({headers: headers});
    this.http.delete('http://localhost:9000/removebasket/' + id.toString(), options)
      .subscribe(
        data => console.log('basket remove sent!', data),
        error => console.error('basket remove error', error)
      );
  }

}
