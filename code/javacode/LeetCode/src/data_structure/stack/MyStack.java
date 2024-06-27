//225. 用队列实现栈
package data_structure.stack;

import java.util.LinkedList;

//只用一个队列
//思想：要取栈顶时，就把队头往后移，直到队头为栈顶那个元素
public class MyStack {
    LinkedList<Integer> list;

    public MyStack() {
        list = new LinkedList<>();
    }

    //始终保持队列的顺序
    public void push(int x) {
        list.addLast(x);
    }

    public int pop() {
        int n = list.size();
        for (int i = 0; i < n - 1; i++)
            list.addLast(list.removeFirst());
        return list.removeFirst();
    }

    public int top() {
        int n = list.size();
        for (int i = 0; i < n - 1; i++)
            list.addLast(list.removeFirst());
        int x = list.getFirst();
        list.addLast(list.removeFirst());
        return x;
    }

    public boolean empty() {
        return list.isEmpty();
    }
}
