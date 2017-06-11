import { Component, OnInit } from '@angular/core';
import {ProductService} from './product.service';
import {Product} from './product';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";

@Component({
  selector: 'app-product',
  templateUrl: './product.component.html',
  styleUrls: ['./product.component.css']
})
export class ProductComponent implements OnInit {

  products: Product[];

  constructor(private productService: ProductService, private route: ActivatedRoute) { }

  ngOnInit() {
    var prodId = this.route.snapshot.params['id'];
    if(prodId) {
      this.showProductsFromCategory(prodId);
    } else {
      this.showAllProducts();
    }
  }

  showProductsFromCategory(id: number) {
    this.productService.getProductsFromCategory(id).subscribe(data => this.products = data);
  }

  showAllProducts() {
    this.productService.getProducts().subscribe(data => this.products = data);
  }

}
