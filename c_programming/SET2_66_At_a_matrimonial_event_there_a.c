#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int men, women;
        scanf("%d %d", &men, &women);
          if (men >= 100 || women >= 100) {
            printf("Invalid Input\n");
            continue;
        }
        
        int count[120] = {0};
        for (int i = 0; i < men; i++) {
            char s[120];
            scanf("%s", s);
            for (int j = 0; j < women; j++) {
                count[j] += s[j] - '0';
            }
        }
        
        int collisions = 0;
        for (int j = 0; j < women; j++) {
            collisions += count[j] * (count[j] - 1) / 2;
        }
        printf("%d\n", collisions);
    }
    return 0;
}
