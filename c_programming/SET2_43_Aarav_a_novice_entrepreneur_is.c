#include <stdio.h>

int main() {
    int cp, sp;
    scanf("%d%d", &cp, &sp);
    if (cp >= 3270 || cp <= 1940  || sp >= 7050 || sp <= 1460)
        printf("Invalid input.\n");
    else if(sp > cp)
        printf("Profit\n");
    else if (sp < cp)
        printf("Loss\n");
    else
        printf("No Profit No Loss\n");
}
