#include <stdio.h>

int main() {
    int aravspeed, aaronspeed, speeddiff;
    scanf("%d", &aravspeed);
    scanf("%d", &aaronspeed);
    
    if(aravspeed < 20 || aravspeed > 100 || aaronspeed < 20 || aaronspeed > 100) {
        printf("Invalid input\n");
    } else {
        speeddiff = (aravspeed > aaronspeed) ? (aravspeed - aaronspeed) : (aaronspeed - aravspeed);
        printf("%d\n", speeddiff);
    }
    return 0;
}
