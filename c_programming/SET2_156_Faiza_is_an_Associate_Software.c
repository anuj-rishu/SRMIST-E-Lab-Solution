#include <stdio.h>
#include <math.h>

struct EMI {
    float principal, rate, time;
} pay;

int main() {
    scanf("%f%f%f", &pay.principal, &pay.rate, &pay.time);
    if (pay.principal < 1 || pay.principal > 1000 || pay.rate < 1 || pay.rate > 1000 || pay.time < 1 || pay.time > 1000)
        printf("Invalid\n");
    else {
        pay.rate /= 1200;
        pay.time *= 12;
        printf("%.2f\n", (pay.principal * pay.rate * pow(1 + pay.rate, pay.time)) / (pow(1 + pay.rate, pay.time) - 1));
    }
    return 0;
}
