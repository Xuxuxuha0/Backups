package behavioral.visitor.impl;


import behavioral.visitor.Visitor;

public class DisplayVisitor implements Visitor {
    //第一种访问方式
    @Override
    public void visit(Mouse mouse) {
        System.out.println("Display Mouse.");
    }

    @Override
    public void visit(Keyboard keyboard) {
        System.out.println("Display Keyboard.");
    }

    @Override
    public void visit(Monitor monitor) {
        System.out.println("Display Monitor.");
    }
}