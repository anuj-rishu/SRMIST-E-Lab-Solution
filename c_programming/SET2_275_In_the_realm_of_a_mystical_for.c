#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int a;

bool attacked(int board[a][a],int n,int x,int y) {
    int i, j;
    for(i=0;i<a;i++) {
        for(j=0;j<a;j++) {
            if (board[i][j] && (i == x || j == y || i + j == x + y || i - j == x - y))
                return true;
        }
    }
    return false;
}

bool solve(int board[a][a], int n, int row) {
    if (row >= a) return true;
    int i;
    for(i=0;i<a;i++) {
        if (!attacked(board, a, i, row)) {
            board[i][row] = 1;
            if (solve(board, a, row + 1))
                return true;
            board[i][row] = 0;
        }
    }
    return false;
}

int main() {
    if (scanf("%d", &a) != 1) return 0;
    int board[a][a];
    memset(board, 0, sizeof(board));
    int i, j;
    if (solve(board, a, 0)) {
        for(i=0;i<a;i++) {
            for(j=0;j<a;j++)
                printf("%d ",board[j][i]);
            printf("\n");
        }
    } else {
        printf("Not possible\n");
    }
    return 0;
}
