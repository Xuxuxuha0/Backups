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
}
void mul(SparseMatrix &A, SparseMatrix &C)
{
    SparseMatrix result;
    result.rows = A.rows;
    result.cols = C.rows;
    int *rowsizeA = (int *)malloc(sizeof(int) * (A.rows + 5));
    int *rowsizeC = (int *)malloc(sizeof(int) * (C.rows + 5));
    int *rowstartA = (int *)malloc((A.rows + 5) * sizeof(int));
    int *rowstartC = (int *)malloc((C.rows + 5) * sizeof(int));
    int i, j, temp, count = 0; // temp:临时存储行列相乘的结果、count:result中元素个数
    for (i = 0; i <= A.rows; i++)
        rowsizeA[i] = 0;
    for (i = 0; i <= C.rows; i++)
        rowsizeC[i] = 0;

    for (i = 0; i < A.terms; i++)
        rowsizeA[A.elem[i].row]++;
    for (i = 0; i < C.terms; i++)
        rowsizeC[C.elem[i].row]++;

    rowstartA[0] = 0;             //初始化
    for (i = 1; i <= A.rows; i++) //计算
        rowstartA[i] = rowstartA[i - 1] + rowsizeA[i - 1];
    rowstartC[0] = 0;             //初始化
    for (i = 1; i <= C.rows; i++) //计算
        rowstartC[i] = rowstartC[i - 1] + rowsizeC[i - 1];

    for (i = 1; i <= A.rows; i++) // A的第i行
        if (rowsizeA[i] == 0)     // A的第i行为空
            continue;
        else
        {
            for (j = 1; j <= C.rows; j++) // C的第j行(即B的第j列)
                if (rowsizeC[j] == 0)
                    continue;
                else
                {
                    int ea = rowstartA[i], ec = rowstartC[j], sizea = rowsizeA[i], sizec = rowsizeC[j]; //需注意含义
                    temp = 0;
                    while (sizea > 0 && sizec > 0)
                    {
                        if (A.elem[ea].col == C.elem[ec].col)
                        {
                            temp += A.elem[ea++].data * C.elem[ec++].data;
                            sizea--;
                            sizec--;
                        }
                        else
                        {
                            if (A.elem[ea].col > C.elem[ec].col)
                            {
                                ec++;
                                sizec--;
                            }
                            else
                            {
                                ea++;
                                sizec--;
                            }
                        }
                    }
                    if (temp != 0)
                    {
                        result.elem[count].row = i;
                        result.elem[count].col = j;
                        result.elem[count].data = temp;
                        count++;
                    }
                }
        }
    result.terms = count;
    cout << result.rows << endl;
    cout << result.cols << endl;
    cout << result.terms << endl;
    for (i = 0; i < count; i++)
        cout << result.elem[i].row << ',' << result.elem[i].col << ',' << result.elem[i].data << endl;
}
int main()
{
    SparseMatrix a, b, c;
    cin >> a.rows >> a.cols >> a.terms;
    for (int i = 0; i < a.terms; i++)
        cin >> a.elem[i].row >> a.elem[i].col >> a.elem[i].data;
    cin >> b.rows >> b.cols >> b.terms;
    for (int i = 0; i < b.terms; i++)
        cin >> b.elem[i].row >> b.elem[i].col >> b.elem[i].data;
    FastTranspos(b, c); //由于ab都是行优先输入，先把b转置为c(列优先)，a*b转化为a*c的特殊形式
    mul(a, c);
}
