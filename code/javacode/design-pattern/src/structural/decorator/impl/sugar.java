package structural.decorator.impl;

import structural.decorator.Beverage;
import structural.decorator.Condiment;

//加料1
public class sugar extends Condiment {

    public sugar(Beverage beverage) {
        this.beverage = beverage;
        price = 2.0;
    }

    @Override
    public double allPrice() {
        return beverage.allPrice() + price;
    }
}
