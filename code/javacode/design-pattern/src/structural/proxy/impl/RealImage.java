package structural.proxy.impl;

import structural.proxy.Image;

public class RealImage implements Image {

    private String fileName;

    public RealImage(String fileName) {
        this.fileName = fileName;
        //从磁盘加载，并存储在fileName
        System.out.println("Loading " + fileName);
    }

    @Override
    public void display() {
        //已经加载过了，直接展示
        System.out.println("Displaying " + fileName);
    }
}
