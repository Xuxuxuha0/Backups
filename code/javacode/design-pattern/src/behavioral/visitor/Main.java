package behavioral.visitor;

import behavioral.visitor.impl.DisplayVisitor;
import behavioral.visitor.impl.Mouse;
import behavioral.visitor.impl.UseVisitor;

public class Main {
    public static void main(String[] args) {
        Visitor v1 = new DisplayVisitor();
        ComputerPart mouse = new Mouse();
        mouse.accept(v1);

        Visitor v2 = new UseVisitor();
        mouse.accept(v2);
    }
}
