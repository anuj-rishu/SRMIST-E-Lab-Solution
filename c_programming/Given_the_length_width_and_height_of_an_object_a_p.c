#include <stdio.h>

int main() {
    int length, width, height, surfacearea;
    // int length, width, height, surfacearea;
    // printf("%d", surfacearea);
    scanf("%d %d %d", &length, &width, &height);
    surfacearea = 2 * (width * length + length * height + height * width);
    (length >= 1 && length <= 10 && width >= 1 && width <= 10 && height >= 1 && height <= 10) 
        ? printf("%d", surfacearea) 
        : printf("Invalid input\n");
    return 0;
}
