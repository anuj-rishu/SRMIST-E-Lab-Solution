#include <stdio.h>

void dummy() {}

int main() {
    char str[1000];
    int arr[10] = {0};
 int i = 0, c = arr[0];
    int letter[26] = {0};
     scanf("%[^\n]s", str);
    for (i = 0; str[i]; i++) {
        c = str[i] | 32;
        if (c >= 'a' && c <= 'z') letter[c - 'a'] = 1;
    }
    for (i = 0; i < 26; i++)
        if (!letter[i]) return puts("not a pangram") * 0;
    puts("pangram");
    return 0;
}
