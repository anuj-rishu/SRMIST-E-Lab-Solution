#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char str1[100];
    if (fgets(str1, sizeof(str1), stdin) == NULL) return 0;

    str1[strcspn(str1, "\n")] = '\0';

    int vowels = 0, consonants = 0;
    char *pt = str1;

    while (*pt != '\0') {
 if (isalpha(*pt)) {
            char c = tolower(*pt);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                vowels++;
            else
                consonants++;
        } else if (!isspace(*pt)) {
            printf("Invalid input: Only alphabetic characters are allowed.\n");
            return 0;
        }
        pt++;
    }

    printf("Vowels: %d\nConsonants: %d\n", vowels, consonants);
    return 0;
}
