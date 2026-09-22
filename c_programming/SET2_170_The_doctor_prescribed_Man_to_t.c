#include <stdio.h>

int main() {
    int t, x, y;
    scanf("%d", &t);
    if (t>5) printf("Invalid input\n");
    else while(t--) {
        scanf("%d%d", &x, &y);
        if(x<=y/3) printf("yes\n");
        else printf("no\n");
    }
}
