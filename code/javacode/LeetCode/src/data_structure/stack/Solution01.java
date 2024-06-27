//20. 有效的括号
package data_structure.stack;

import java.util.LinkedList;

//注意switch的新语法
public class Solution01 {
    public boolean isValid(String s) {
        LinkedList<Character> stack = new LinkedList<>();
        int len = s.length();
        for (int i = 0; i < len; i++) {
            char c = s.charAt(i);
            if (c == '(' || c == '{' || c == '[')
                stack.addLast(c);
            else {
                if (stack.isEmpty() || !switch (c) {
                    case ')' -> stack.removeLast() == '(';
                    case '}' -> stack.removeLast() == '{';
                    case ']' -> stack.removeLast() == '[';
                    default -> throw new IllegalStateException("Unexpected value: " + c);
                })
                    return false;
            }
        }
        return stack.isEmpty();
    }
}
