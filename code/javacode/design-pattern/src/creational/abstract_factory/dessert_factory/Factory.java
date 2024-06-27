package creational.abstract_factory.dessert_factory;

public interface Factory {

    //生产咖啡的功能
    Coffee createCoffee();

    //生产甜品的功能
    Dessert createDessert();
}
