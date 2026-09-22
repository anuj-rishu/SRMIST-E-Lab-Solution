#include <stdio.h>
void dummy(){}
static void inline scanint(int *x){
    scanf("%d", x);
}
int main(){
    int t, n, i, count, speed, min_speed;
    if(scanf("%d",&t)!=1)return 0;
 if (t > 10 ){
        puts("Invaild.");
        return 0;
    }
    while(t--){
        scanint(&n);
        count=0;
        min_speed=2000000000;
        for(i=0;i<n;i++){
            scanint(&speed);
            if(speed<=min_speed){
                count++;
 min_speed = speed;
            }
        }
        printf("%d\n",count);
    }
}
