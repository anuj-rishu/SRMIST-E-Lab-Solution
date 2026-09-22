#include <stdio.h>

void dummy() {}

int sumd(int n) {
    return n ? n % 10 + sumd(n / 10) : 0;
}

int superd(int num) {
    if(num<10) return num;
    return superd(sumd(num));
}

int main() {
    int num,k;
    if (scanf("%d%d", &num, &k) != 2 || num < 1 || num > 10000 || k < 1 || k > 100)
        return puts("Invaild Input") * 0;
    printf("%d\n", superd(sumd(num) * k));
}
