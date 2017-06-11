import { NgModule } from '@angular/core';
import { HttpModule } from '@angular/http';
import { RouterModule } from "@angular/router";
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { LoginComponent } from './login/login.component';
import { BasketComponent } from './basket/basket.component';
import { ProductComponent } from './product/product.component';
import { CategoryComponent } from './category/category.component';
import { ShowProductComponent } from './showProduct/showProduct.component';
import { ShippingFormComponent } from './shippingForm/shippingForm.component';
import { PageNotFoundComponent } from './not-found/not-found.component';

import {LoginService} from "./login/login.service";
import {OrderService} from "./shippingForm/order.service";
import {BasketService} from "./basket/basket.service";
import {ProductService} from "./product/product.service";
import {CategoryService} from "./category/category.service";

import { CanActivateViaOAuthGuard } from './oAuth.canActivateGuard';


@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    BasketComponent,
    ProductComponent,
    CategoryComponent,
    ShowProductComponent,
    ShippingFormComponent,
    PageNotFoundComponent
  ],
  imports: [
    HttpModule,
    FormsModule,
    BrowserModule,
    ReactiveFormsModule,
    RouterModule.forRoot([
      { path: '.', component: AppComponent},
      { path: 'products', component: ProductComponent},
      { path: 'category/:id', component: ProductComponent},
      { path: 'categories', component: CategoryComponent},
      { path:  'showProduct/:id', component: ShowProductComponent},
      { path: 'login', component: LoginComponent},
      { path: 'callback', component: LoginComponent},
      { path: 'shippingForm', component: ShippingFormComponent},
      { path: 'basket', component: BasketComponent, canActivate: [CanActivateViaOAuthGuard]},
      { path: 'moreparams/:tytul/:opis', component: ProductComponent},
      { path: '', redirectTo: 'products', pathMatch: 'full'},
      { path: '**', component: PageNotFoundComponent }
      ])
  ],
  providers: [LoginService,
              OrderService,
              BasketService,
              ProductService,
              CategoryService,
              CanActivateViaOAuthGuard],
  bootstrap: [AppComponent]
})
export class AppModule { }
