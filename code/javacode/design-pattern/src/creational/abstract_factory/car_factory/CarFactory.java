package creational.abstract_factory.car_factory;

public interface CarFactory {
    public Car createCar();

    public Engine createEngine();

    public Wheel createWheel();
}
