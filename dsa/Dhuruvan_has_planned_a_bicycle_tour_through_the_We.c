void dummy(){}
#include <stdio.h>
int a[105];
int main() {
    int T, t, n, i;
    scanf("%d", &T);
    for(t=0;t<T;t++) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) scanf("%d", &a[i]);
        int c = 0;
        for(i=1;i<n-1;i++) {
            if (a[i] > a[i-1] && a[i] > a[i+1]) c++;
        }
        printf("%d\n", c);
    }
    return 0;
}
