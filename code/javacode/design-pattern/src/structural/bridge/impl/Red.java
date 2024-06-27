package structural.bridge.impl;

import structural.bridge.Color;

public class Red implements Color {
    @Override
    public void draw() {
        System.out.print("Red ");
    }
}
