package structural.bridge.impl;

import structural.bridge.Color;

public class Green implements Color {
    @Override
    public void draw() {
        System.out.print("Green ");
    }
}
