package structural.bridge.impl;

import structural.bridge.Color;
import structural.bridge.Shape;

public class Circle extends Shape {
    public void draw() {
        color.draw(); //调用color的方法
        System.out.println("Circle");
    }
}
