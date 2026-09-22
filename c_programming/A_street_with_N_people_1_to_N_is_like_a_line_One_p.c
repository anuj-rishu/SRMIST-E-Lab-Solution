#include <stdio.h>
int main(){
    int c;
    scanf("%d", &c);
    if(c>5) return puts("Invalid input") * 0;
    int x[10];
    for(int i=0;i<c;i++) scanf("%d", &x[i]);
    int min = 100, max = 0;
    for(int i=0;i<c;i++){
        int count = 1;
        for(int j = i - 1; j >= 0 && x[j+1] - x[j] <= 2; j--) count++;
        for(int j = i + 1; j < c && x[j] - x[j-1] <= 2; j++) count++;
        if(count>max) max = count;
        if(count<min) min = count;
    }
    printf("%d %d\n", min, max);
    return 0;
}
