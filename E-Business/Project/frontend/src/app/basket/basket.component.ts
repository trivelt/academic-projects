import { Component, OnInit } from '@angular/core';
import {BasketService} from './basket.service';
import {Basket} from './basket';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";

@Component({
  selector: 'app-product',
  templateUrl: './basket.component.html',
})
export class BasketComponent implements OnInit {

  baskets: Basket[];

  constructor(private basketService: BasketService, private route: ActivatedRoute) { }

  ngOnInit() {
    this.basketService.getBasket().subscribe(data => this.baskets = data);
    console.log(this.route.snapshot.params);
  }

}
