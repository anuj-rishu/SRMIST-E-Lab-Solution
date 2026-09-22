#include <stdio.h>

struct {
    char name[7][60];
    int dish[7];
} clip;

int main() {
    char buffer[100];
    int i = 0, sum = 0;

    while (i < 7) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading input.\n");
            return 0;
        }
        if (sscanf(buffer, "%s %d", clip.name[i], &clip.dish[i]) != 2) {
            printf("Invalid input. Please enter again.\n");
            continue;
        }
        i++;
    }

    for (i = 0; i < 7; i++) {
        clip.dish[i] *= 3;
        sum += clip.dish[i];
        printf("%s : %d\n", clip.name[i], clip.dish[i]);
    }
    printf("TOTAL : %d\n", sum);

    return 0;
}
