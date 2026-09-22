void dummy(){}
#include <stdio.h>

int main() {
    int n, t;
    if (scanf("%d", &n) != 1) return 0;
    int array[n];
    for(int i=0;i<n;i++) scanf("%d", &array[i]);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if(array[i]>array[j]) {
                t = array[i]; array[i] = array[j]; array[j] = t;
            }
    for (int i = 0; i < n - 1; i += 2) {
        t = array[i]; array[i] = array[i + 1]; array[i + 1] = t;
    }
    for (int i = 0; i < n; i++) printf("%d ", array[i]);
    printf("\n");
    return 0;
}
