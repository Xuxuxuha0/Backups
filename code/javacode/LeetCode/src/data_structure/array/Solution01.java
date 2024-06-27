//283. 移动零
package data_structure.array;

//双指针
public class Solution01 {
    public void moveZeroes(int[] nums) {
        int len = nums.length;
        int p1 = 0, p2 = 0;
        //p1始终指向已经处理好的序列的下一位
        //p2一直移动，如果p2指向的数非0，则赋给p1
        //最后把[p1,len-1]区间的全部赋值0
        while (p2 < len) {
            if (nums[p2] != 0)
                nums[p1++] = nums[p2];
            p2++;
        }
        for (int i = p1; i < len; i++)
            nums[i] = 0;
    }
}
