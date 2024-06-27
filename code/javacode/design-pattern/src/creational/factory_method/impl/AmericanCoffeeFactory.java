package creational.factory_method.impl;

import creational.factory_method.Coffee;
import creational.factory_method.CoffeeFactory;

public class AmericanCoffeeFactory implements CoffeeFactory {

    public Coffee createCoffee() {
        return new AmericanCoffee();
    }
}
