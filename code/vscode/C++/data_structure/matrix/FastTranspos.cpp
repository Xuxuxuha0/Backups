#include <iostream>
using namespace std;
#define maxsize 100
typedef struct
{
    int row, col, data; //行、列、元素
} Triple;
typedef struct
{
    int rows, cols, terms; //总行、总列、非零总元素数
    Triple elem[maxsize];  //三元表
} SparseMatrix;
void FastTranspos(SparseMatrix &A, SparseMatrix &B) //快速转置(假设横纵坐标从0开始，但最大值可以等于总行、总列)
{
    int *rowsize = (int *)malloc((A.cols + 5) * sizeof(int));  //用于存放A中每列元素数(也是B中每行元素数)
    int *rowstart = (int *)malloc((A.cols + 5) * sizeof(int)); //用于存放B中每行开始的位置
    int i, j;
    B.cols = A.rows;
    B.rows = A.cols;
    B.terms = A.terms;
    for (i = 0; i <= A.cols; i++) //初始化
        rowsize[i] = 0;
    for (i = 0; i < A.terms; i++) //计算
        rowsize[A.elem[i].col]++;
    rowstart[0] = 0;              //初始化
    for (i = 1; i <= A.cols; i++) //计算
        rowstart[i] = rowstart[i - 1] + rowsize[i - 1];
    cout << "num:";
    for (i = 1; i <= A.cols; i++)
        cout << rowsize[i] << ',';
    cout << endl;
    cout << "cpot:";
    for (i = 1; i <= A.cols; i++)
        cout << rowstart[i] + 1 << ',';
    cout << endl;
    for (i = 0; i < A.terms; i++) //把A中每行三元表写入B中对应位置
    {
        j = rowstart[A.elem[i].col];
        B.elem[j].col = A.elem[i].row;
        B.elem[j].row = A.elem[i].col;
        B.elem[j].data = A.elem[i].data;
        rowstart[A.elem[i].col]++;
    }
    free(rowsize);
    free(rowstart);
    for (i = 0; i < A.terms; i++)
        cout << B.elem[i].row << ',' << B.elem[i].col << ',' << B.elem[i].data << endl;
}
int main()
{
    SparseMatrix a;
    cin >> a.rows >> a.cols >> a.terms;
    for (int i = 0; i < a.terms; i++)
        cin >> a.elem[i].row >> a.elem[i].col >> a.elem[i].data;
    SparseMatrix b;
    FastTranspos(a, b);
}
