package behavioral.strategy.impl;

import behavioral.strategy.QuackBehavior;

public class QuackGUA implements QuackBehavior {
    @Override
    public void Quack() {
        //呱呱叫
        System.out.println("Quack:GUA GUA");
    }
}
