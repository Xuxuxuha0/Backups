//645. 错误的集合
package data_structure.array;

import java.util.Arrays;

//数学解法
public class Solution06 {
    public int[] findErrorNums(int[] nums) {
        int[] res = new int[2];
        int len = nums.length;
        int CORRECT_SUM = (1 + len) * len / 2;
        int DISTINCT_SUM = Arrays.stream(nums).distinct().sum();
        int NUMS_SUM = Arrays.stream(nums).sum();
        res[1] = CORRECT_SUM - DISTINCT_SUM;
        res[0] = NUMS_SUM - DISTINCT_SUM;
        return res;
    }
}