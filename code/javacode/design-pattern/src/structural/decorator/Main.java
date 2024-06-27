package structural.decorator;

import structural.decorator.impl.Coffee;
import structural.decorator.impl.Milk;
import structural.decorator.impl.Water;
import structural.decorator.impl.sugar;

public class Main {
    public static void main(String[] args) {
        //coffee = 10
        Beverage b1 = new Coffee();
        System.out.println(b1.allPrice());

        //water + milk + sugar + milk
        //1+5+2+5 = 13
        Beverage b2 = new Water();
        b2 = new Milk(b2);
        b2 = new sugar(b2);
        b2 = new Milk(b2);
        System.out.println(b2.allPrice()); //递归调用
    }
}
