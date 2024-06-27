#include <iostream>
using namespace std;

#define maxSize 100
#define maxValue 1000000

typedef int WeightType;

typedef struct //最小生成树的边
{
    int v1, v2;
    WeightType cost;
} MSTENode;

typedef struct
{
    MSTENode Edges[maxSize];
    int n;
} MinSpanTree;
