#include <stdio.h>

struct player {
    char name[100];
    int p;
};

int main() {
    int l;
    if (scanf("%d", &l) != 1 || l > 11) {
        printf("Invaild.\n");
        return 0;
    }
    struct player a[11];
     int i,s=0;
    for(i=0;i<l;i++) {
        scanf("%s%d", a[i].name, &a[i].p);
        s += a[i].p;
    }
    printf("Total Points:%d\n", s);
    return 0;
}
