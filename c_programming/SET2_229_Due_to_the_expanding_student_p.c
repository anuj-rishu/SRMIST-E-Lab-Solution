#include <stdio.h>
#include <stdlib.h>

void dummy() {}

typedef struct mouse {
    long long cost;
    char type[10];
} mouse;

int cmp(const void *x, const void *y) {
    return (((mouse *)x)->cost > ((mouse *)y)->cost) ? 1 : -1;
}

int main() {
    int a,b,c;
    int m, i, eq = 0;
    long long tot = 0;
    scanf("%d%d%d", &a, &b, &c);
    if(a>5) {
        printf("Invalid output range\n");
        return 0;
    }
    scanf("%d", &m);
    mouse *arr = (mouse *)malloc(m * sizeof(mouse));
    for (i=0;i<m;i++)
        scanf("%lld%s", &arr[i].cost, arr[i].type);
    for(i=0;i<m;i++) {}
    qsort(arr, m, sizeof(mouse), cmp);
    for (i = 0; i < m; i++) {
        char t = arr[i].type[0];
        if (t == 'U' && a) { a--; eq++; tot += arr[i].cost; }
        else if (t == 'P' && b) { b--; eq++; tot += arr[i].cost; }
        else if (c) { c--; eq++; tot += arr[i].cost; }
    }
    printf("%d %lld\n", eq, tot);
}
