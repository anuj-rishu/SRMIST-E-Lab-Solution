#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n < 1 || n > 50) {
        printf("Invalid input for password length\n");
        return 0;
    }
    char s[60];
    scanf("%s", s);
    int no1 = 0, no2 = 0, no3 = 0, no4 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') no1 = 1;
        else if (s[i] >= 'a' && s[i] <= 'z') no2 = 1;
        else if (s[i] >= 65 && s[i] <= 90) no3 = 1;
        else no4 = 1;
    }
    int missing = 0;
    if (no1 == 0) missing++;
    if (no2 == 0) missing++;
    if (no3 == 0) missing++;
    if (no4 == 0) missing++;
    int count = missing;
    if (n < 6 && count == 0) printf("%d\n", 6 - n);
    else if (n < 6) {
        int ans = 6 - n > missing ? 6 - n : missing;
        printf("%d\n", ans);
    } else {
        printf("%d\n", missing);
    }
}
