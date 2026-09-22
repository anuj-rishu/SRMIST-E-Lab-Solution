#include <stdio.h>
#include <math.h>

int check(int N) {
     int i;
    for(i=2;i<=sqrt(N);i++)
        if (N % i == 0) return 1;
    return 0;
}

int main() {
    int T, N;
    scanf("%d", &T);
    if(T<2||T>100000) {
        printf("Invalid Input\n");
        return 0;
    }
    while (T--) {
        scanf("%d",&N);
        if (check(N))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
