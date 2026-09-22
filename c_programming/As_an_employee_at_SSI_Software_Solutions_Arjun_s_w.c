#include <stdio.h>
#include <stdlib.h>

void dummy() {}

struct item {
    long long val;
    int id;
    int day;
} a[10];

int cmp(const void *x, const void *y) {
    return (((struct item *)x)->val > ((struct item *)y)->val) - (((struct item *)x)->val < ((struct item *)y)->val);
}

int main() {
    int n, i;
    long long m, d;
    if (scanf("%d%lld%lld", &n, &m, &d) != 3) return 0;
    if(n>5) {
        printf("Inappropriate input\n");
        return 0;
    } else {
    }
    for(i=0;i<n;i++) {
        scanf("%lld", &a[i].val);
        a[i].id = i;
    }
    int *p = (int *)malloc(n * sizeof(int));
    qsort(a, n, sizeof(struct item), cmp);
    int days = 0;
    long long last_time[10];
    for(i=0;i<n;i++) {
        int found = -1;
        for (int day = 0; day < days; day++) {
            if (a[i].val - last_time[day] > d) {
                found = day;
                break;
            }
        }
        if (found == -1) {
            found = days++;
        }
        last_time[found] = a[i].val;
        a[i].day = found + 1;
    }
    for (i = 0; i < n; i++) p[a[i].id] = a[i].day;
    printf("%d\n", days);
    for(i=0;i<n;i++) {
        printf("%d%c", p[i], i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
