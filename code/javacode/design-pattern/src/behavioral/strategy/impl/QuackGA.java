package behavioral.strategy.impl;

import behavioral.strategy.QuackBehavior;

public class QuackGA implements QuackBehavior {
    @Override
    public void Quack() {
        //嘎嘎叫
        System.out.println("Quack:GA GA");
    }
}
