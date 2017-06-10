import { Component, OnInit } from '@angular/core';
import {CategoryService} from './category.service';
import {Category} from './category';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";

@Component({
  selector: 'app-product',
  templateUrl: './category.component.html',
})
export class CategoryComponent implements OnInit {

  categories: Category[];

  productForm: FormGroup;

  constructor(private categoryService: CategoryService, private route: ActivatedRoute) { }

  ngOnInit() {
    this.categoryService.getCategories().subscribe(data => this.categories = data);
    console.log(this.route.snapshot.params);
  }

}
