#include <stdio.h>

int main() {
    int arr[10], size, i;
    int *ptr;

    scanf("%d",&size);
    if (size > 10) {
        printf("The size is beyond the allowed range\n");
        return 0;
    }

    ptr=&arr[0];
    for(i=0;i<size;i++) {
        scanf("%d", ptr + i);
    }

    for (i = size - 1; i >= 0; i--) {
        printf("%d ", *(ptr + i));
    }

    return 0;
}
