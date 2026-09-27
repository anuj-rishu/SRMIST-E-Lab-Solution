#include <stdio.h>

int has21(int x) {
    while (x > 0) {
        if (x % 100 == 21) return 1;
        x /= 10;
    }
    return 0;
}

void solve() {
    int n;
    scanf("%d", &n);
    if(n%21==0) {
        printf("The streak is broken!\n");
    } else if (has21(n)) {
        printf("The streak is broken!\n");
    } else {
        printf("The streak lives still in our heart!\n");
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
