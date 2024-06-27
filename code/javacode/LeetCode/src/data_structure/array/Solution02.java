//566. 重塑矩阵
package data_structure.array;

public class Solution02 {
    public int[][] matrixReshape(int[][] mat, int r, int c) {
        int m = mat.length, n = mat[0].length;
        if (m * n != r * c)
            return mat;

        int a = 0, b = 0;
        int[][] newMat = new int[r][c];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                //二维矩阵<-->一维矩阵的下标的相互映射关系
                int x = i * n + j;
                newMat[x / c][x % c] = mat[i][j];
            }
        return newMat;
    }
}
