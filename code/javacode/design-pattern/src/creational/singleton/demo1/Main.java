package creational.singleton.demo1;

/*饿汉式 + 静态变量*/
public class Main {
    public static void main(String[] args) {
        //创建Singletion类的对象
        Singleton instance = Singleton.getInstance();
    }
}
