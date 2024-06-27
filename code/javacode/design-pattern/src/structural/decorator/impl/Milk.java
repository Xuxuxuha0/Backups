package structural.decorator.impl;

import structural.decorator.Beverage;
import structural.decorator.Condiment;

//加料2
public class Milk extends Condiment {

    public Milk(Beverage beverage) {
        this.beverage = beverage;
        price = 5.0;
    }

    @Override
    public double allPrice() {
        return beverage.allPrice() + price;
    }
}
