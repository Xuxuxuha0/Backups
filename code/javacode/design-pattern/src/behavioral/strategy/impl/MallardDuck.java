package behavioral.strategy.impl;

import behavioral.strategy.Duck;

public class MallardDuck extends Duck {
    public MallardDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new QuackGA();
    }


    @Override
    public void display() {
        System.out.println("i am MallardDuck");
    }
}
