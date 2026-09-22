#include <stdio.h>

char a[20][20];
int count;

void biggest(int i,int j,int n) {
    if (i < 0 || i >= n || j < 0 || j >= n || a[i][j] != 'T')
        return;
    a[i][j] = 'W';
    count++;
    biggest(i + 1, j, n);
    biggest(i - 1, j, n);
    biggest(i, j + 1, n);
    biggest(i, j - 1, n);
}

int main() {
    int n, i, j, max = 0;
    scanf("%d", &n);
    if(n>10) {
        printf("Number of characters are exceeds the limit\n");
        return 0;
    }
    for(i=0;i<n;i++)
        scanf("%s", a[i]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if (a[i][j] == 'T') {
                count = 0;
                biggest(i,j,n);
                if (count > max)
                    max = count;
            }
    printf("%d\n", max);
    return 0;
}
