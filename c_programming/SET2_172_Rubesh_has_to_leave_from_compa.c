#include <stdio.h>
int main(){
    int t, X, Y;
    scanf("%d", &t);
    if(t>3) return puts("Invali input") * 0;
    while (t--){
        scanf("%d%d", &X, &Y);
        if (X < Y) puts("First");
        else if (X > Y) puts("Second");
        else puts("Any");
    }
}
