#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j;
    scanf("%d",&n);
    if(n>5) {
        printf("The input value is out of range\n");
        return 0;
    }

    char**grid=malloc(sizeof(char*)*n);
    for(i=0;i<n;i++) {
        grid[i]=malloc(n+1);
        scanf("%s", grid[i]);
    }

    for(i=1;i<n-1;i++)
        for(j=1;j<n-1;j++)
            if (grid[i][j] > grid[i-1][j] && grid[i][j] > grid[i+1][j] &&
                grid[i][j] > grid[i][j-1] && grid[i][j] > grid[i][j+1])
                grid[i][j] = 'X';

    for(i=0;i<n;i++)
        printf("%s\n", grid[i]);

    return 0;
}
