package creational.abstract_factory.dessert_factory.impl;

import creational.abstract_factory.dessert_factory.Coffee;
import creational.abstract_factory.dessert_factory.Dessert;
import creational.abstract_factory.dessert_factory.Factory;

public class AmericanDessertFactory implements Factory {
    public Coffee createCoffee() {
        return new AmericanCoffee();
    }

    public Dessert createDessert() {
        return new MatchaMousse();
    }
}
