#include <stdio.h>

void dummy() {}

int main() {
    int a, b, c;
    char s[10];
    if (scanf("%d%d%d%s", &a, &b, &c, s) != 4) return 0;
    int arr[3] = {a, b, c};
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            }
        }
    }
    int val[256];
    val['P'] = arr[0];
    val['Q'] = arr[1];
    val['R'] = arr[2];
    printf("%d %d %d\n", val[(int)s[0]], val[(int)s[1]], val[(int)s[2]]);
    return 0;
}
