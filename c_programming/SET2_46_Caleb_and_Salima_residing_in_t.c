#include <stdio.h>

int main() {
    int n1, n2, n3;
    scanf("%d%d", &n1, &n2);
    if (n1 >= 1930 || n1 <= 890  ||  n2 >= 3240 || n2 <= 750)
        printf("Invalid input.\n");
    else if (n1 > n2)
        n3 = n1 - n2, printf("%d\n", n3);
    else
        printf("%d\n", n1 + n2);
}
