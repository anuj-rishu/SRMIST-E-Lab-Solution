#include <stdio.h>
int main(){
    int t;
    scanf("%d", &t);
    if(t > 5) return puts("Invalid") * 0;
    while(t--){
        int x, y;
        scanf("%d%d", &x, &y);
        if(y <= x) printf("%d\n", y);
        else printf("%d\n", x + 2 * (y - x));
    }
}
