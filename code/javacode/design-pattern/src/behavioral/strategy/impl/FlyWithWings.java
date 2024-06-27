package behavioral.strategy.impl;

import behavioral.strategy.FlyBehavior;

public class FlyWithWings implements FlyBehavior {
    @Override
    public void fly() {
        System.out.println("i am flying");
    }
}
