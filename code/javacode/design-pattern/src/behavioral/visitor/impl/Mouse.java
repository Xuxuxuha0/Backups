package behavioral.visitor.impl;

import behavioral.visitor.ComputerPart;
import behavioral.visitor.Visitor;

public class Mouse implements ComputerPart {
    @Override
    public void accept(Visitor visitor) {
        //接受访问
        visitor.visit(this);
    }
}
