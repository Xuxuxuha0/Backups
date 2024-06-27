package structural.bridge;

public abstract class Shape {
    protected Color color; //属性必须是protected


    protected void setColor(Color color) {
        this.color = color;
    }

    public abstract void draw();
}
