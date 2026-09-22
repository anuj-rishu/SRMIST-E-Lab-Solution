#include <stdio.h>

int main() {
    int t;
     float p, i, interest, amount;
    scanf("%f %f %d", &p, &i, &t);
      if (p <= 9999 || p >= 21601 || i <= 5.0 || i >= 12.0 || t <= 4 || t >= 16) {
        printf("Invalid Input\n");
        return 0;
    }
     interest = (p * i * t) / 100;
    amount = p + interest;
    printf("Interest after %d Years = $%.2f\nTotal Amount after %d Years = $%.2f\n", t, interest, t, amount);
    return 0;
}
