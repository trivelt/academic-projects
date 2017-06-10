import { Injectable } from '@angular/core';
import {Http, Headers, RequestOptions, URLSearchParams, Response} from "@angular/http";
import {Product} from "./product";
import {Observable} from 'rxjs/Rx';
import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';

@Injectable()
export class ProductService {

  constructor(private http: Http) { }

  getProducts() {
    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    const options = new RequestOptions({headers: headers});

    return this.http.get('http://localhost:9000/', options)
      .map(response => <Product[]>response.json());
  }

  getProductsFromCategory(id: number) {
    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    let params: URLSearchParams = new URLSearchParams();
    params.set('id', id.toString());

    const options = new RequestOptions({headers: headers, search: params});

    return this.http.get('http://localhost:9000/category', options)
      .map(response => <Product[]>response.json());
  }

  getProduct(id: number) : Observable<Product> {
    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    let params: URLSearchParams = new URLSearchParams();
    params.set('id', id.toString());

    const options = new RequestOptions({headers: headers, search: params});

    return this.http.get('http://localhost:9000/product', options)
      .map(response => <Product>response.json()).catch((error: any) => Observable.throw(error.json().error || 'Server error' ));
  }

  sendToPlay(formData) {
    const serializedForm = JSON.stringify(formData);
    // console.log(serializedForm);

    const headers: Headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');

    const options = new RequestOptions({headers: headers});

    this.http.post('http://localhost:9000/newproduct', serializedForm, options)
      .subscribe(
        data => console.log('wyslane!', data),
        error => console.error('nie bangla', error)
      );
  }

}
