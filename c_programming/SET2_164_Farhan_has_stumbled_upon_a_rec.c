#include <stdio.h>
#include <string.h>

struct first {
    char str1[12];
};

int main() {
    int t,i,sum,j,count;
    scanf("%d", &t);
    if (t < 1 || t > 5) {
        printf("Invaild\n");
        return 0;
    }
    while (t--) {
        struct first d1[4], d2[4];
         for(i=0;i<4;i++) scanf("%s", d1[i].str1);
         for(i=0;i<4;i++) scanf("%s", d2[i].str1);
        count = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (strcmp(d1[i].str1, d2[j].str1) == 0) {
                    count++;
                    break;
                }
            }
        }
        sum = count;
        if (sum >= 2) printf("similar\n");
        else printf("dissimilar\n");
    }
    return 0;
}
