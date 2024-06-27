//485. 最大连续 1 的个数
package data_structure.array;

//思路：
//维护当前连续1的个数cur，当前最大连续1的个数max
//遍历数组，如果当前元素为1，cur++
//如果当前元素为0，则先比较cur和max，再把cur清零
public class Solution03 {
    public int findMaxConsecutiveOnes(int[] nums) {
        int len = nums.length;
        int max = 0, cur = 0;
        for (int i = 0; i < len; i++) {
            if (nums[i] == 1)
                cur++;
            else {
                max = Math.max(max, cur);
                cur = 0;
            }
        }
        //考虑以1结尾的情况
        max = Math.max(max, cur);
        return max;
    }
}
