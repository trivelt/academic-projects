import { Component, OnInit } from '@angular/core';
import {FormControl, FormGroup, Validators} from "@angular/forms";
import {ActivatedRoute} from "@angular/router";
import {Order} from "./order";

@Component({
  selector: 'shipping-form',
  templateUrl: './shippingForm.component.html',
})
export class ShippingFormComponent implements OnInit {

  productForm: FormGroup;

  shippmentMethods = ["Poczta Polska - przesylka ekonomiczna",
                      "Poczta Polska - przesylka priorytetowa",
                      "Kurier Pocztex24",
                      "Paczkomat",
                      "Kurier DHL"];

  paymentMethods = ["Za pobraniem",
                    "Przelew tradycyjny",
                    "Przelewy24.pl",
                    "Karta platnicza",
                    "PayPal",
                    "Bitcoin"]

  model = new Order();

  constructor(private route: ActivatedRoute) { }

  ngOnInit() {
      this.model.paymentMethod = this.paymentMethods[0];
      this.model.shippmentMethod = this.shippmentMethods[1];
    // var prodId = this.route.snapshot.params['id'];
  }

  showSummary() {
    console.log("showSummary clicked, address=" + this.model.address);
  }


}
