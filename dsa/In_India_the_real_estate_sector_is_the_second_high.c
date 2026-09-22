void dummy(){}
#include <stdio.h>

void makeheap(int x[],int n) {
    for (int i = 1; i < n; i++) {
        int val = x[i];
        int s = i;
        int f = (s - 1) / 2;
        while (s > 0 && x[f] < val) {
            x[s] = x[f];
            s = f;
            f = (s - 1) / 2;
        }
        x[s] = val;
    }
}

void heapsort(int x[],int n) {
    makeheap(x, n);
    for (int i = n - 1; i > 0; i--) {
        int val = x[i];
        x[i] = x[0];
        int f = 0, s;
        if (i == 1) s = -1;
        else s = 1;
        if (i > 2 && x[2] > x[1]) s = 2;
        while (s >= 0 && val < x[s]) {
            x[f] = x[s];
            f = s;
            s = 2 * f + 1;
            if (s + 1 <= i - 1 && x[s] < x[s + 1]) s++;
            if (s > i - 1) s = -1;
        }
        x[f] = val;
    }
}

int a[100005];

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n, b;
        scanf("%d%d", &n, &b);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        makeheap(a,n);
        heapsort(a,n); 
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (b >= a[i]) {
                b -= a[i];
                ans++;
            } else break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
