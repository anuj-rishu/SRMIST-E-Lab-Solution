#include <stdio.h>

int row[1005];
int col[1005];

int main() {
    int r, c, m, n;
    scanf("%d %d", &r, &c);
    
    int arr[r][c];
    int arrTemp[r][c];
    
    for(m=0;m<r;m++) {
        for(n=0; n<c; n++) {
            scanf("%d", &arr[m][n]);
            if (arr[m][n]) {
                row[m] = 1;
                col[n] = 1;
            }
        }
    }
    
    for(m=0;m<r;m++) {
        for(n=0; n<c; n++) {
            arrTemp[m][n] = row[m] | col[n];
            printf("%d%c", arrTemp[m][n], (n == c - 1) ? '\n' : ' ');
        }
    }
    return 0;
}
