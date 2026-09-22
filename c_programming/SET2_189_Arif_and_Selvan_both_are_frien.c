#include <stdio.h>
#include <string.h>

void f(char *ch) {
    int count = 0;
    while (*ch != '\0') {
        count++;
        ch++;
    }
    printf("Length of the string: %d\n", count);
}

int main() {
    char str1[10000];
    if (fgets(str1, sizeof(str1), stdin) == NULL || strlen(str1) > 50) {
        printf("Invalid input. Please enter a string with at most 50 characters.\n");
        return 0;
    }
    str1[strcspn(str1, "\n")] = 0;
    f(str1);
    return 0;
}
