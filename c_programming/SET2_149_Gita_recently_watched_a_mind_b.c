#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void printInputs(char (*matrix)[100],int R,int C){}
void get_col(char (*m)[100], int R, int c, char *out){
    for(int i=0; i<R; i++) out[i] = m[i][c];
    out[R] = 0;
}
int has_col(char (*m)[100], int R, int C){
    char buf[105];
    int f = 0;
    for(int j=0; j<C; j++){
        get_col(m, R, j, buf);
        f |= (strcasestr(buf, "spoon") != NULL) | (strcasestr(buf, "cipher") != NULL);
    }
    return f;
}
int has_row(char (*m)[100], int R){
    int f = 0, i;
    for(i=0;i<R;i++)
        f |= (strcasestr(m[i], "spoon") != NULL) | (strcasestr(m[i], "cipher") != NULL);
    return f;
}
int main(){
    int T, R, C, i;
    char matrix[100][100];
    if(scanf("%d", &T) != 1) return 0;
    if(T>10) return puts("Invalid Input") * 0;
    while(T--){
        scanf("%d%d", &R, &C);
        for(i=0;i<R;i++) scanf("%s", matrix[i]);
        puts((has_row(matrix, R) | has_col(matrix, R, C)) ? "YES" : "NO");
    }
    return 0;
}
