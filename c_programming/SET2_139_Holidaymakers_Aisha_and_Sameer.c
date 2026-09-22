#include <stdio.h>

int checkPrime(int n) {
    int i, isPrime = 1;
    if (n == 0 || n == 1) isPrime = 0;
    else {
        for(i = 2; i <= n/2; ++i) {
            if(n % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }
    return isPrime;
}

int main() {
    int n, i;
    scanf("%d", &n);
    if (n > 200) {
        printf("Invalid input.\n");
        return 0;
    }
    for (i = 2; i <= n / 2; ++i) {
        if (checkPrime(i) && checkPrime(n - i)) {
            printf("%d = %d + %d\n", n, i, n - i);
        }
    }
}
