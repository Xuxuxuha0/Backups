package creational.abstract_factory.car_factory.impl;

import creational.abstract_factory.car_factory.Car;
import creational.abstract_factory.car_factory.Engine;
import creational.abstract_factory.car_factory.Wheel;

public class MyCar implements Car {
    private Engine engine;
    private Wheel wheel;

    public MyCar(Engine engine, Wheel wheel) {
        this.engine = engine;
        this.wheel = wheel;
        System.out.println("finish assemble MyCar!");
    }
}
