#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int count[26]={0};
    int i, len;
    scanf("%s", str);
    len = strlen(str);
     if (len < 1 || len > 10) {
        printf("Invalid string length.\n");
        return 0;
    }
    for (i = 0; i < len; i++)
        count[str[i] - 'a']++;
    for (i = 0; i < 26; i++)
        printf("%d ", count[i]);
    return 0;
}
