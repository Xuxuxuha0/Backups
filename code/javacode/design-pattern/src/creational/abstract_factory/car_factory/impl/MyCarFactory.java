package creational.abstract_factory.car_factory.impl;

import creational.abstract_factory.car_factory.Car;
import creational.abstract_factory.car_factory.CarFactory;
import creational.abstract_factory.car_factory.Engine;
import creational.abstract_factory.car_factory.Wheel;

public class MyCarFactory implements CarFactory {

    @Override
    public Car createCar() {
        System.out.println("create MyCar using following items:");
        return new MyCar(createEngine(), createWheel());
    }

    @Override
    public Engine createEngine() {
        System.out.println("create MyEngine...");
        return new MyEngine();
    }

    @Override
    public Wheel createWheel() {
        System.out.println("create MyWheel...");
        return new MyWheel();
    }
}
