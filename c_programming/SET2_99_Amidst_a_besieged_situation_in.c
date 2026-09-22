#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    char tag[10];
    if (scanf("%s", tag) != 1) return 0;
  if (strlen(tag) > 10)
     if (strlen(tag) > 10)
        return printf("Invalid input\n") * 0;
    int ok = 1;
    if (strchr("AEIOUY", tag[2]))
        ok = 0;
    else if ((tag[0] + tag[1]) % 2 || (tag[3] + tag[4]) % 2 || (tag[4] + tag[5]) % 2 || (tag[7] + tag[8]) % 2)
        ok = 0;
    puts(ok ? "Allowed" : "Arrest");
}
