# include "compute.h"


string compute(int n) {
    int i, j, sum, count=0;

    for (i = 1; i < n * n * n; i += 2) {
        sum = 0;
        count = 0;
        for (j = i; j < n * n * n; j += 2) {
            sum = sum + j;
            count++;
            if (((n * n * n == sum) && (count == n)) || count > n)
                break;
        }
        if ((sum == n * n * n) && (count == n))
            break;
    }
    stringstream ss;
    ss << n << "*" << n << "*" << n << "=";
    for (int k = 0; k < count; k++) {
        if (count - k == 1)
            ss << i + 2 * k;
        else
            ss << i + 2 * k << "+";
    }
    return ss.str();
}