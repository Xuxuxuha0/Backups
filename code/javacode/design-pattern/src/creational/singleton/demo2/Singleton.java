package creational.singleton.demo2;

/*懒汉式 + 线程安全 + 效率高*/
public class Singleton {

    //私有构造方法
    private Singleton() {
    }

    //volatile：可以保证可见性和有序性，防止空指针异常
    private static volatile Singleton instance;

    //对外提供公共的访问方式
    public static Singleton getInstance() {
        //第一次判断，如果instance的值不为null，直接返回对象(提高了效率)
        if (instance == null) {
            //如果该对象没被创建，则进入创建
            //这里可能同时有多个线程进入，因此加锁
            synchronized (Singleton.class) {
                //第二次判断，防止如下情况：
                //  线程1拿到锁，线程2等待
                //  线程1创建完对象，释放锁
                //  线程2拿到锁，（如果没有二次判断），则又会创建对象
                if (instance == null) {
                    instance = new Singleton();
                }
            }
        }
        return instance;
    }
}
