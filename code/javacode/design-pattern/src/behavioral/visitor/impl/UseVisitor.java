package behavioral.visitor.impl;

import behavioral.visitor.Visitor;

public class UseVisitor implements Visitor {
    //第二种访问方式
    @Override
    public void visit(Mouse mouse) {
        System.out.println("use mouse");
    }

    @Override
    public void visit(Keyboard keyboard) {
        System.out.println("use keyboard");
    }

    @Override
    public void visit(Monitor monitor) {
        System.out.println("use monitor");
    }
}
