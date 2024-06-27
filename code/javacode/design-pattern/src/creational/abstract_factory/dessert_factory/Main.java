package creational.abstract_factory.dessert_factory;

import creational.abstract_factory.dessert_factory.impl.AmericanDessertFactory;
import creational.abstract_factory.dessert_factory.impl.ItalyDessertFactory;

public class Main {
    public static void main(String[] args) {
        //创建的是意大利风味甜品工厂对象
//        Factory factory = new ItalyDessertFactory();
        Factory factory = new AmericanDessertFactory();
        //获取拿铁咖啡和提拉米苏甜品
        Coffee coffee = factory.createCoffee();
        Dessert dessert = factory.createDessert();

        System.out.println(coffee.getName());
        dessert.show();
    }
}
