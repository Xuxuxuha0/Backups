//232. 用栈实现队列
package data_structure.stack;

import java.util.LinkedList;

public class MyQueue {
    LinkedList<Integer> input, output;

    public MyQueue() {
        input = new LinkedList<>();
        output = new LinkedList<>();
    }

    //新增
    public void push(int x) {
        input.addLast(x);
    }

    //移除并返回头部元素
    public int pop() {
        //只要output不为空，则output的栈顶一定是队列的头
        //当output为空时，input的值倒给output又可以得到新的队列
        if (output.isEmpty())
            inToOut();
        return output.removeLast();
    }

    //返回头部元素
    public int peek() {
        if (output.isEmpty())
            inToOut();
        return output.getLast();
    }

    public boolean empty() {
        return input.isEmpty() && output.isEmpty();
    }

    //把input的值倒给output
    public void inToOut() {
        while (!input.isEmpty())
            output.addLast(input.removeLast());
    }
}

