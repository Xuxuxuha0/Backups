package structural.decorator.impl;

import structural.decorator.Beverage;

//饮料2
public class Water extends Beverage {
    public Water() {
        price = 1.0;
    }

    @Override
    public double allPrice() {
        return price;
    }
}
