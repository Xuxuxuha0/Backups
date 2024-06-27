package behavioral.observer.impl;

import behavioral.observer.DisplayElement;
import behavioral.observer.Observer;

public class CurrentConditionsDisplay implements Observer, DisplayElement {

    private float temperature;
    private float humidity;
    private WeatherData weatherData; //存储数据中心

    public CurrentConditionsDisplay(WeatherData weatherData) {
        this.weatherData = weatherData;
        // 创建对象时就要注册
        weatherData.registerObserver(this);
    }

    @Override
    public void display() {
        System.out.println("current conditons:" + temperature + "F," + humidity + "%");
    }

    @Override
    public void update() {
        this.temperature = weatherData.getTemperature();
        this.humidity = weatherData.getHumidity();
        display();
    }

    public void removeMyself() {
        // 移除
        weatherData.removeObserver(this);
    }
}
