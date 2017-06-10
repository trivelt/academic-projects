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

  productForm: FormGroup;

  constructor(private productService: ProductService, private route: ActivatedRoute) { }

  ngOnInit() {
    this.productService.getProducts().subscribe(data => this.products = data);

    this.productForm = new FormGroup({
      tytul: new FormControl('tytul', Validators.required),
      opis: new FormControl('opis', Validators.required)
    });

    console.log(this.route.snapshot.params);
  }

  addProduct(event) {
    console.log(event);
    console.log(this.productForm.value);
    this.productService.sendToPlay(this.productForm.value);
  }

}
