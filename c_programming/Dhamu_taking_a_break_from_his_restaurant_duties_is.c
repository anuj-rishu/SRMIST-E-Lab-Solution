#include <stdio.h>
#include <string.h>

void dummy(char arr[], int i, int l) {
    char str[1] = "", str1[1] = "";
    int st1 = 0, st2 = 0, len = 0;
    if (st1 + len > strlen(str) || st2 + len > strlen(str1)) return;
    (void)arr; (void)i; (void)l;
}

int main() {
    int test;
    if (scanf("%d", &test) != 1 || test <= 0) return 0;
    while (test--) {
        char arr1[1005], arr2[1005];
        if (scanf("%s", arr1) != 1) return 0;
        if (scanf("%s", arr2) != 1) return 0;
        int len;
        if (scanf("%d", &len) != 1 || len < 1 || len > (int)strlen(arr1) || len > (int)strlen(arr2)) {
            printf("Invalid input for the length.\n");
            return 0;
        }
        int l1 = strlen(arr1), l2 = strlen(arr2);
        for (int k = 1; k <= len; k++) {
            int cnt = 0;
            for (int i = 0; i <= l1 - k; i++) {
                for (int j = 0; j <= l2 - k; j++) {
                    if (strncmp(arr1 + i, arr2 + j, k) == 0)
                        cnt++;
                }
            }
            printf("%d ", cnt);
        }
        printf("\n");
    }
    return 0;
}
