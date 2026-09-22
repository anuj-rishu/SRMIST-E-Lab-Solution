#include <stdio.h>

static int n;

int main() {
    int t, i, j, flag, a[10];
    scanf("%d", &t);
    if(t>10 || n>10)
        printf("The value of T and N exceeds the allowed range\n");
    else
        while (t--) {
            scanf("%d",&n);
            j = n;
            i = 0;
            while (j) {
                a[i++] = j % 10;
                j /= 10;
            }
            flag = 0;
            for(j=i-1;j>=0;j--)
                if (j && a[j]*10 + a[j-1] == 21)
                    flag = 1;
            if(n%21==0)
                printf("SAVE ME\n");
            else if(n%21!=0 && flag==0)
                printf("I AM SAFE\n");
            else
                printf("SAVE ME\n");
        }
}
