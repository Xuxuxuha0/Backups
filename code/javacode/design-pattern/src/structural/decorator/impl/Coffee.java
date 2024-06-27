package structural.decorator.impl;

import structural.decorator.Beverage;

//饮料1
public class Coffee extends Beverage {
    public Coffee() {
        price = 10.0;
    }

    @Override
    public double allPrice() {
        return price;
    }
}
