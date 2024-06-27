package behavioral.observer;

import behavioral.observer.impl.CurrentConditionsDisplay;
import behavioral.observer.impl.WeatherData;

public class Main {
    public static void main(String[] args) {
        //主题
        WeatherData weatherData = new WeatherData();
        //观察者(自动注册)
        CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay(weatherData);
        //更新主题的参数(自动通知观察者)
        weatherData.setMeasurements(80, 65, 30.4f);
        weatherData.setMeasurements(82, 70, 29.2f);
        weatherData.setMeasurements(78, 90, 29.2f);
        //移除自己，不想"订阅了"
        currentDisplay.removeMyself();
        weatherData.setMeasurements(100, 100, 100f);
    }
}