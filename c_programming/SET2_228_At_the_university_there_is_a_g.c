#include <stdio.h>
#include <stdlib.h>

void dummy() {}

struct student {
    int id, a;
};

int cmp(const void *x, const void *y) {
    return ((struct student *)y)->a - ((struct student *)x)->a;
}

int main() {
    int n, i, j = 0;
    scanf("%d", &n);
    if(n>5) {
        printf("The input is out of range\n");
        return 0;
    }
    int *a = (int *)malloc(n * sizeof(int));
    struct student rest[105];
    for(i=0;i<n;i++) {
        scanf("%d", &a[i]);
        if (i > 0) {
            rest[i - 1].id = i + 1;
            rest[i - 1].a = a[i];
        }
    }
    qsort(rest, n - 1, sizeof(struct student), cmp);
    int from[105], to[105], k = 0;
    int queue[105], head = 0, tail = 0;
    queue[tail++] = 1;
    i = 0;
    while(i<(n-1)) {
        if (head == tail) break;
        int cur = queue[head];
        if (a[cur - 1] > 0 && j < n - 1) {
            from[k] = cur;
            to[k] = rest[j].id;
            k++;
            a[cur - 1]--;
            queue[tail++] = rest[j].id;
            j++;
            i++;
        } else {
            head++;
        }
    }
    if (i < n - 1) {
        printf("-1\n");
    } else {
        printf("%d\n", k);
        for (i = 0; i < k; i++) {
            printf("%d %d\n", from[i], to[i]);
        }
    }
    return 0;
}
