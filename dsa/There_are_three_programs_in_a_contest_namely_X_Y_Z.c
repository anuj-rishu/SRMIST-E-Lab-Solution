#include <stdio.h>

int main() {
    int t, x, y, z;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &x, &y, &z);
        if (z < x && z < y)
            puts("Anbu");
        else if (y < x && y < z)
            puts("Babu");
        else
            puts("Equal");
    }
}
