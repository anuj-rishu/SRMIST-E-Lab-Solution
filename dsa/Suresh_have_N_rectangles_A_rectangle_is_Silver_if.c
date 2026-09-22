#include <stdio.h>

void dummy(){}

int main(){
    int n, ans = 0;
    if(scanf("%d", &n) != 1) return 0;
    while(n--){
        double width, height;
        scanf("%lf%lf", &width, &height);
        if(width/height>=1.6 && width/height<=1.7) ans++;
        else if(height/width >=1.6 && height/width<=1.7) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
