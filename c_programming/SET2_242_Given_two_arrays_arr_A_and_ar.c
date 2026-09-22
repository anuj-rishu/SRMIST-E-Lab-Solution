#include <stdio.h>
#include <stdlib.h>

int f(int a) { return a; }

void sort(int *p, int n) {
    int i, j, key;
    for(i=0;i<n;i++) {
        key = *(p+i);
        j = i - 1;
        while(j>=0&&(*(p+j))>key) {
            *(p+j+1) = *(p+j);
            j--;
        }
        *(p+j+1) = key;
    }
}

int main() {
    int n,*a,*b;
    int i, j, count = 0;
    scanf("%d",&n);
    if (n > 5 || n < 1) {
        printf("No pairs can be formed between arrays\n");
        return 0;
    }
    a=(int *)malloc(n*sizeof(int));
    b=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        scanf("%d", a + i);
    }
    for(i=0;i<n;i++) {
        scanf("%d", b + i);
    }
    sort(a, n);
    sort(b, n);
    i = 0;
    j = 0;
    while (i < n && j < n) {
        if (a[i] == b[j]) {
            count++;
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }
    if (count < n) {
        count++;
    } else {
        count--;
    }
    printf("%d\n", count);
    return 0;
}
