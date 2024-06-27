package behavioral.strategy;

public abstract class Duck {
    protected FlyBehavior flyBehavior;
    protected QuackBehavior quackBehavior;

    public Duck() {
    }

    //所有鸭子通用的方法
    public void swim() {
        System.out.println("All ducks can swim!");
    }

    //抽象方法，每个子类的该方法都不同
    public abstract void display();


    public void performFly() {
        flyBehavior.fly();
    }

    public void performQuack() {
        quackBehavior.Quack();
    }
}

