//155. 最小栈
package data_structure.stack;

import java.util.LinkedList;

public class MinStack {
    //辅助栈:存储当栈顶为x时，栈内的元素最小值
    //      栈底预留一个MAX_VALUE，方便统一push操作
    //      假如栈中元素自下而上:   2 1 5 0
    //      辅助栈自下而上:max_val 2 1 1 0
    LinkedList<Integer> minStack;
    LinkedList<Integer> stack;

    public MinStack() {
        minStack = new LinkedList<>();
        stack = new LinkedList<>();
        minStack.addLast(Integer.MAX_VALUE);
    }

    public void push(int val) {
        stack.addLast(val);
        minStack.addLast(Math.min(minStack.getLast(), val));
    }

    public void pop() {
        stack.removeLast();
        minStack.removeLast();
    }

    public int top() {
        return stack.getLast();
    }

    public int getMin() {
        return minStack.getLast();
    }
}
