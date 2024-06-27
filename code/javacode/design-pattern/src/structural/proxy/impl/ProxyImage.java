package structural.proxy.impl;

import structural.proxy.Image;

public class ProxyImage implements Image {

    private RealImage realImage; //存储实际对象
    private String fileName;

    public ProxyImage(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void display() {
        //代理的作用：如果该图像已经加载过了，就可以直接显示
        if (realImage == null) {
            realImage = new RealImage(fileName);
        }
        realImage.display();
    }
}
