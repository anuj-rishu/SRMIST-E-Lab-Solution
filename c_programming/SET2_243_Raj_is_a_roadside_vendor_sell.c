#include <stdio.h>
#include <stdlib.h>

int f(int a) { return a; }

void colorsort(int *p,int n) {
    int i, j, key;
    for(i=0;i<n;i++) {
        key = *(p + i);
        j = i - 1;
        while(j>=0&&(*(p+j))>key) {
            *(p + j + 1) = *(p + j);
            j--;
        }
        *(p + j + 1) = key;
    }
}

int main() {
    int n, i, j = 0;
    scanf("%i",&n);
    if(n>10) {
        printf("Please provide n not greater than 10\n");
        return 0;
    }
    int *p = (int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++) {
        scanf("%d", p + i);
    }
    colorsort(p, n);
    for(i=0;i<n-1;i++) {
        if (*(p + i) == *(p + i + 1)) {
            j++;
            i++;
        }
    }
    printf("%d\n", j);
    return 0;
}
