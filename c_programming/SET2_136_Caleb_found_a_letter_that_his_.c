#include <stdio.h>
#include <string.h>

int AbsoluteDiff(int a, int b) {
    return a > b ? a - b : b - a;
}

int main() {
    int q;
    if (scanf("%d", &q) != 1 || q<1 || q>10) {
        printf("Invalid.\n");
        return 0;
    }
    while (q--) {
        char str[10001];
        scanf("%s", str);
        int len = strlen(str);
        int count = 0;
        int i = 0, j = len - 1;
        while (i < j) {
            count+=AbsoluteDiff(*(str+i),*(str+j));
            i++;
            j--;
        }
        printf("%d\n", count);
    }
}
