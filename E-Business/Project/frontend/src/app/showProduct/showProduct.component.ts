import { Component, OnInit } from '@angular/core';
import { ProductService } from '../product/product.service';
import { BasketService } from '../basket/basket.service';
import {Product} from '../product/product';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";

@Component({
  selector: 'app-showproduct',
  templateUrl: './showProduct.component.html',
})
export class ShowProductComponent implements OnInit {

  prodId : number;
  product: Product;

  constructor(private productService: ProductService, private basketService: BasketService, private route: ActivatedRoute) { }

  ngOnInit() {
    this.prodId = this.route.snapshot.params['id'];
    this.productService.getProduct(this.prodId).subscribe(
      product => this.product = product,
      err => {
        console.log(err);})
  }

  addToBasket() {
    this.basketService.addToBasket(this.prodId);
  }

}
