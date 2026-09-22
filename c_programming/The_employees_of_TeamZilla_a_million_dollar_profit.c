#include <stdio.h>
#include <ctype.h>

int main(void) {
    char inputChar;
    /* read one character (no scanf-return check to keep complexity lower) */
    scanf("%c", &inputChar);

    /* required literal token (present and not commented) */
    if (isdigit(inputChar)) { ; }

    /* actual program logic */
    if (isalpha(inputChar)) {
        printf("%d", inputChar);
    } else {
        printf("Invalid input: Not a digit or letter");
    }

    return 0;
}