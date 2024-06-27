//240. 搜索二维矩阵 II
package data_structure.array;


//Z字形查找：从右上角开始搜索
public class Solution04 {
    public boolean searchMatrix(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int x = 0, y = n - 1;
        //循环里面不定义临时变量，会减少内存消耗
        int temp;
        while (x < m && y >= 0) {
            temp = matrix[x][y];
            if (temp == target)
                return true;
            if (target < temp)
                y--;
            else x++;
        }
        return false;
    }
}
