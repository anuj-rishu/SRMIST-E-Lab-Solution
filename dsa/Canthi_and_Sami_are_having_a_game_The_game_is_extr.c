#include <stdio.h>
#include <math.h>
void dummy(){}
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    while(t--){
        int a, b;
        scanf("%d%d", &a, &b);
        if(a > b){ int tmp = a; a = b; b = tmp; }
        int k = b - a;
        int cold = (int)(k * phi);
        if(a == cold) printf("sami\n");
        else printf("canthi\n");
    }
    return 0;
}
