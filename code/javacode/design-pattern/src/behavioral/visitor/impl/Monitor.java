package behavioral.visitor.impl;

import behavioral.visitor.ComputerPart;
import behavioral.visitor.Visitor;

public class Monitor  implements ComputerPart {

    @Override
    public void accept(Visitor visitor) {
        visitor.visit(this);
    }
}
