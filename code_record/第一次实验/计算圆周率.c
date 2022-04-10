#include <math.h>
#include <stdio.h>

double item(int K) {
    double k = (double)K;
    double m1 = pow(16.0, k);
    double a1 = 4.0 / (8.0 * k + 1.0);
    double a2 = 2.0 / (8.0 * k + 4.0);
    double a3 = 1.0 / (8.0 * k + 5.0);
    double a4 = 1.0 / (8.0 * k + 6.0);
    double m2 = a1 - a2 - a3 - a4;
    return m2 / m1;
}

int main() {
    double ep;
    scanf("%lf", &ep);
    double res = 0.0;
    int k = 0;
    while (1) {
        double ak = item(k);
        res += ak;
        if (fabs(ak) - ep < 0) {
            break;
        }
        k++;
    }
    printf("%d\n", k);
    return 0;
}



