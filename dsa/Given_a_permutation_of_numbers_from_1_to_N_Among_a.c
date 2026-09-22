#include <stdio.h>
int stck[100005], a[100005];
int top = -1;
int main() {
    int n;
    scanf("%d", &n);
    long long count = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        while (top!=-1 && stck[top]<a[i]) {
            count++;
            top--;
        }
        if (top != -1) count++;
        stck[++top] = a[i];
    }
    printf("%lld", count);
    return 0;
}
