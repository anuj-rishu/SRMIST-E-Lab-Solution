#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1 || (t < 1 || t > 10)) {
        printf("Invalid input.\n");
        return 0;
    }
    while (t--) {
        char str[100];
        if (scanf("%s", str) != 1) return 0;
        int len = strlen(str);
        int maxl = len / 2;
        if (str[0] == '0' || len < 2) {
            printf("NO\n");
            continue;
        }
        long long arr[100];
        int found = 0;
        for (int i = 1; i <= maxl; i++) {
            arr[0] = 0;
            for (int p = 0; p < i; p++) arr[0] = (arr[0] * 10) + str[p] - '0';
            int k = 1;
            int j = i;
            int l = 0;
            while (j < len) {
                arr[k] = 0;
                long long next = arr[k - 1] + 1;
                while (j < len && arr[k] < next) {
                    arr[k] = (arr[k] * 10) + str[j] - '0';
                    j++;
                }
                if (arr[k] != next) {
                    l = 1;
                    break;
                }
                k++;
            }
            if (j == len && l == 0) {
                printf("YES %lld\n", arr[0]);
                found = 1;
                break;
            }
        }
        if (!found) printf("NO\n");
    }
    return 0;
}
