package creational.factory_method.impl;

import creational.factory_method.CoffeeFactory;
import creational.factory_method.Coffee;

public class LatteCoffeeFactory implements CoffeeFactory {

    public Coffee createCoffee() {
        return new LatteCoffee();
    }
}
