import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import { HttpModule } from '@angular/http';


import { AppComponent } from './app.component';
import { ProductComponent } from './product/product.component';
import { CategoryComponent } from './category/category.component';
import { ShowProductComponent } from './showProduct/showProduct.component';
import { PageNotFoundComponent } from './not-found/not-found.component';

import {RouterModule} from "@angular/router";
import {ProductService} from "./product/product.service";
import {CategoryService} from "./category/category.service";


@NgModule({
  declarations: [
    AppComponent,
    ProductComponent,
    PageNotFoundComponent,
    CategoryComponent,
    ShowProductComponent
  ],
  imports: [
    BrowserModule,
    HttpModule,
    FormsModule,
    ReactiveFormsModule,
    RouterModule.forRoot([
      { path: '.', component: AppComponent},
      { path: 'products', component: ProductComponent},
      { path: 'category/:id', component: ProductComponent},
      { path: 'categories', component: CategoryComponent},
      { path:  'showProduct/:id', component: ShowProductComponent},
      { path: 'moreparams/:tytul/:opis', component: ProductComponent},
      { path: '', redirectTo: 'products', pathMatch: 'full'},
      { path: '**', component: PageNotFoundComponent }
      ])
  ],
  providers: [ProductService,
              CategoryService],
  bootstrap: [AppComponent]
})
export class AppModule { }
