package data_structure.stack;


import java.util.Arrays;
import java.util.LinkedList;

//单调栈+循环数组

//假设:4 2 3 4 3 1
//正向思维：想要知道1的res，就要去4 2 3 4 3序列里面找
//单调栈，逆向思维:当第一个3进来时，就可以确定3之前比3小的数字的res，例如2的res就等于3
//这就相当于:想要1的res，就必须在它后面拼接4 2 3 4 3序列，由这个序列里面某个数就可以得到1的res
//所以就形成循环数组:4 2 3 4 3 1 4 2 3 4 3
public class Solution03 {
    public int[] nextGreaterElements(int[] nums) {
        int len = nums.length;
        int[] res = new int[len];
        Arrays.fill(res, -1);
        //存的是下标
        LinkedList<Integer> stack = new LinkedList<>();
        int temp;
        //处理循环数组：遍历[0,2*len-2]，并使用%len来处理下标
        for (int i = 0; i < 2 * len - 1; i++) {
            int index = i % len;
            while (!stack.isEmpty() && nums[index] > nums[stack.getLast()]) {
                //如果还没找到结果(注意括号表达式的使用)
                if (res[(temp = stack.removeLast())] == -1)
                    res[temp] = nums[index];
            }
            stack.addLast(index);
        }
        return res;
    }
}
