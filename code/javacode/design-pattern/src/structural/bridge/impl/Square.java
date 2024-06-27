package structural.bridge.impl;

import structural.bridge.Shape;

public class Square extends Shape {
    @Override
    public void draw() {
        color.draw();
        System.out.println("Square");
    }
}
