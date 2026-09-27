#include <stdio.h>

int a[500005];
int sz = 0;

int binarySearch(int a[],int item,int low,int high) {
    if (high <= low)
        return (item > a[low]) ? low : low + 1;
    int mid = (low + high) / 2;
    if (item == a[mid])
        return mid + 1;
    if (item > a[mid])
        return binarySearch(a, item, low, mid - 1);
    return binarySearch(a, item, mid + 1, high);
}

void insert(int val) {
    if (sz == 0) {
        a[0] = val;
        sz = 1;
        return;
    }
    int pos = binarySearch(a, val, 0, sz - 1);
    for (int i = sz - 1; i >= pos; i--) {
        a[i + 1] = a[i];
    }
    a[pos] = val;
    sz++;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    while (n--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int p;
            scanf("%d", &p);
            insert(p);
        } else {
            if (sz < 3) {
                printf("Not enough enemies\n");
            } else {
                printf("%d\n", a[sz / 3 - 1]);
            }
        }
    }
    return 0;
}
