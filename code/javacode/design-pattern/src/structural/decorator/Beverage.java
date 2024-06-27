package structural.decorator;

public abstract class Beverage {
    protected double price; //饮料or加料 本身的价格

    public abstract double allPrice(); //累积的价格
}
