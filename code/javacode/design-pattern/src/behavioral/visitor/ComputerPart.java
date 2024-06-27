package behavioral.visitor;

public interface ComputerPart {
    void accept(Visitor visitor);
}
