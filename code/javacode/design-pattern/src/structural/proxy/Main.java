package structural.proxy;

import structural.proxy.impl.ProxyImage;

public class Main {
    public static void main(String[] args) {
        Image image = new ProxyImage("xxx.png");

        // 图像将从磁盘加载
        image.display();

        // 图像不需要从磁盘加载
        image.display();
    }
}
