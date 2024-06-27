//378. 有序矩阵中第 K 小的元素
package data_structure.array;

//二分查找：
//设要求的值为x，设matrix[0][0]=left，matrix[m-1][n-1]=right
//1、假设二维数组变成了排好序的一维数组，则x一定在[left,right]区间内；设mid=left+(right-left)/2，cnt等于[matrix[0][0],mid]区间的个数
//2、如果cnt>=k，则x一定在[left,mid]区间内，此时令right=mid
//3、如果cnt<k，则x一定在[mid+1,right]区间内，此时令left=mid+1
//4、此时就确定了x在新的[left,right]区间内
//5、如果left==right，则x就等于left；否则继续二分

//其他问题：
//1、left一定小于等于right：当right>left时，mid在[left,right)内，无论是right=mid还是left=mid+1，都能保证left<=right
//2、如何求cnt：
// 回到二维数组中，从左下角的值ld开始
// 如果ld<=mid，则ld及其上方所有值都被计入cnt，同时ld指针右移
// 如果ld>mid，则ld指针上移
// 直到ld指针出界
public class Solution05 {
    int m, n, left, right, mid;

    public int kthSmallest(int[][] matrix, int k) {
        m = matrix.length;
        n = matrix[0].length;
        left = matrix[0][0];
        right = matrix[m - 1][n - 1];
        while (left < right) {
            //切记不能写为mid=(left+right)/2，因为当[-5,-4]时，mid=-4，靠近right一边
            mid = left + (right - left) / 2;
            if (check(matrix, k))
                left = mid + 1;
            else right = mid;
        }
        return left;
    }

    public boolean check(int[][] matrix, int k) {
        int cnt = 0, x = m - 1, y = 0;
        while (x >= 0 && y < n) {
            if (matrix[x][y] <= mid) {
                cnt += x + 1;
                y++;
            } else x--;
        }
        return cnt < k;
    }
}

