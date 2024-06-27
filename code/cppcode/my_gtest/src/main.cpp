#include <iostream>
#include "compute/compute.h"
#include <sstream>

using namespace std;

int main() {
    cout << compute(5);
//
//    cout << "main" << endl;
//    int i, j, n, sum, count;
//    printf("\n an integer here please:");
//    scanf("%d", &n);
//
//    printf("\n");
//    for (i = 1; i < n * n * n; i += 2) { //遍历所有奇数
//        sum = 0;
//        count = 0;
//        for (j = i; j < n * n * n; j += 2) {
//            sum = sum + j; //连续奇数，从i开始
//            count++;
//            if (((n * n * n == sum) && (count == n)) || count > n)
//                break;
//        }
//        if ((sum == n * n * n) && (count == n))
//            break;
//    }
//    printf("%d*%d*%d=", n, n, n);
//    for (int k = 0; k < count; k++) {
//        if (count - k == 1)
//            printf("%d", i + 2 * k);
//        else printf("%d+", i + 2 * k);
//    }
//    return 0;
}
