//739. 每日温度
package data_structure.stack;

import java.util.Arrays;
import java.util.LinkedList;

//单调栈思想：
//栈元素存放下标，栈底到栈顶始终保持非降序的温度(同时也保证了下标的升序排列)
//当来一个新的温度，如果栈顶非空，且比栈顶温度高，就一直退栈

//普通思想：把当前温度和后面的温度比较，直到找到一个比他大的
//单调思想：把当前温度和前面的温度比较(这里的前面，指的是还没有得到结果的温度)，只要有比它小的，就能得到对应的结果
public class Solution02 {
    public int[] dailyTemperatures(int[] temperatures) {
        LinkedList<Integer> stack = new LinkedList<>();
        int len = temperatures.length;
        int[] res = new int[len];
        Arrays.fill(res, 0);
        for (int i = 0; i < len; i++) {
            //当栈不为空，且栈顶的温度小于当前的温度，就退栈并更新res
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.getLast()])
                res[stack.getLast()] = i - stack.removeLast();
            //入栈
            stack.addLast(i);
        }
        return res;
    }
}
