package creational.abstract_factory.car_factory;

import creational.abstract_factory.car_factory.impl.MyCarFactory;

public class Main {
    public static void main(String[] args) {
        CarFactory myCarFactory = new MyCarFactory();
        Car myCar = myCarFactory.createCar();
    }
}
