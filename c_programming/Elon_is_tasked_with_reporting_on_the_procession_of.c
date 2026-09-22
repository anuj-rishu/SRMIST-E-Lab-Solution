#include <stdio.h>
#include <string.h>

int main() {
    int r;
    scanf("%d", &r);
    if (r < 1 || r > 10) return printf("Invalid input.\n") * 0;
    while (r--) {
        int len;
        char report[505];
        scanf("%d%s", &len, report);
        int flag = 0;
        for (int i = 0; i < len && flag >= 0; i++) {
            switch (report[i]) {
                case 'H':
                    if (flag == 0) flag = 1;
                    else flag = -1;
                    break;
                case 'T':
                    flag = (flag) ? 0 : -1;
                    break;
                default:
                    break;
            }
        }
        if (flag == 0) printf("Valid\n");
        else printf("Invalid\n");
    }
}
