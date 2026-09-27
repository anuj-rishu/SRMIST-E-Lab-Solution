#include <stdio.h>
#include <string.h>

char str[100005];

int SmallestSubString(char* str) {
    int n = strlen(str), d = 0, h[128] = {0}, c[128] = {0};
    for (int i = 0; i < n; i++) if (!h[(int)str[i]]++) d++;
    int cnt = 0, s = 0, ans = n;
    for (int j = 0; j < n; j++) {
        if (!c[(int)str[j]]++) cnt++;
        if (cnt == d) {
            while (c[(int)str[s]] > 1) c[(int)str[s++]]--;
            int len = j - s + 1;
            if (len < ans) ans = len;
        }
    }
    return ans;
}

int main() {
    scanf("%s", str);
    printf("%d\n", SmallestSubString(str));
    return 0;
}
