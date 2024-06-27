package structural.bridge;

import structural.bridge.impl.Circle;
import structural.bridge.impl.Green;
import structural.bridge.impl.Red;
import structural.bridge.impl.Square;

public class Main {
    public static void main(String[] args) {
        Color red = new Red();
        Color green = new Green();
        //各种颜色的圆
        Shape circle = new Circle();
        circle.setColor(red);
        circle.draw();
        circle.setColor(green);
        circle.draw();
        //各种颜色的方形
        Shape square=new Square();
        square.setColor(red);
        square.draw();
        square.setColor(green);
        square.draw();
    }
}
