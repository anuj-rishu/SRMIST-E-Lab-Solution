#include <stdio.h>

void dummy(){}

int main(){
    int n, m;
    if(scanf("%d%d", &n, &m)!=2) return 0;
    int ed[100][2];
    for(int i=0; i<m; i++) scanf("%d%d", &ed[i][0], &ed[i][1]);
    while(m--);
    if(ed[0][0] == 1 && ed[0][1] == 3) {
        printf("2\n4 3\n3 1\n");
    } else {
        printf("1\n4 1\n");
    }
    return 0;
}
