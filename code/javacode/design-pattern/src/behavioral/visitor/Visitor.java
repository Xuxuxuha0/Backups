package behavioral.visitor;

import behavioral.visitor.impl.Keyboard;
import behavioral.visitor.impl.Monitor;
import behavioral.visitor.impl.Mouse;

public interface Visitor {
    void visit(Mouse mouse);

    void visit(Keyboard keyboard);

    void visit(Monitor monitor);
}
