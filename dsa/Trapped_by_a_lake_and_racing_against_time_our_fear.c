#include <stdio.h>
#include <math.h>

void dummy(){}

int main(){
    char name[105];
    int length;
    double rate, width;
    if(scanf("%s%d%lf%lf", name, &length, &rate, &width) != 4) return 0;
    double speed1 = sqrt(2.0 * rate * (double)length);
    double distance;
    distance=speed1*speed1/9.805;
    printf("%s will reach a speed of %.2f m/s on a %d ramp crossing %.1f of %.1f meters, ",
           name, speed1, length, distance, width);
    if(distance < (width - 5.0)) printf("SPLASH!\n");
    else if(distance <= width) printf("JOVA MADE IT!\n");
    else printf("LIKE A LEGEND!\n");
    return 0;
}
