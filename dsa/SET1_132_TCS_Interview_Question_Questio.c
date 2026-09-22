#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int array[n];
    for(int i=0;i<n;i++) {
        scanf("%d", &array[i]);
    }
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(array[i]>array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    for(int i=0; i+1<n; i+=2) {
        int temp = array[i];
        array[i] = array[i+1];
        array[i+1] = temp;
    }
    for(int i=0; i<n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
