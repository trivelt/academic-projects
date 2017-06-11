import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import { HttpModule } from '@angular/http';
import {RouterModule} from "@angular/router";

import { AppComponent } from './app.component';
import { LoginComponent } from './login/login.component';
import { ProductComponent } from './product/product.component';
import { CategoryComponent } from './category/category.component';
import { ShowProductComponent } from './showProduct/showProduct.component';
import { PageNotFoundComponent } from './not-found/not-found.component';

import {ProductService} from "./product/product.service";
import {CategoryService} from "./category/category.service";
import {LoginService} from "./login/login.service";

import { CanActivateViaOAuthGuard } from './oAuth.canActivateGuard';


@NgModule({
  declarations: [
    AppComponent,
    ProductComponent,
    PageNotFoundComponent,
    CategoryComponent,
    ShowProductComponent,
    LoginComponent
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
      { path: 'categories', component: CategoryComponent, canActivate: [CanActivateViaOAuthGuard]},
      { path:  'showProduct/:id', component: ShowProductComponent},
      { path: 'login', component: LoginComponent},
      { path: '_oauth-callback', component: LoginComponent},
      { path: 'callback', component: LoginComponent},
      { path: 'moreparams/:tytul/:opis', component: ProductComponent},
      { path: '', redirectTo: 'products', pathMatch: 'full'},
      { path: '**', component: PageNotFoundComponent }
      ])
  ],
  providers: [ProductService,
              CategoryService,
              LoginService,
              CanActivateViaOAuthGuard],
  bootstrap: [AppComponent]
})
export class AppModule { }
