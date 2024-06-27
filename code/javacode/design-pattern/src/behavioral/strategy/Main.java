package behavioral.strategy;

import behavioral.strategy.impl.MallardDuck;

public class Main {
    public static void main(String[] args) {
        Duck mallard = new MallardDuck();
        mallard.display(); //选用了MallardDuck
        mallard.swim(); //点击游泳
        mallard.performFly(); //点击飞行
        mallard.performQuack(); //点击叫
    }
}