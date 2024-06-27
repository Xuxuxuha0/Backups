package behavioral.strategy.impl;

import behavioral.strategy.FlyBehavior;

public class FlyNoWay implements FlyBehavior {
    @Override
    public void fly() {
        System.out.println("i cannot fly");
    }
}
