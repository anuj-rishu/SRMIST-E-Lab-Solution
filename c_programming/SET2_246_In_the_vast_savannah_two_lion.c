#include <stdio.h>
#include <stdlib.h>

int lionandhyena(int a,int b) {
    if (a < b) return 1;
    return 0;
}

int main() {
    int q,x,y,z,*ans,i;
    scanf("%d", &q);
    if(q>10) {
        printf("The input value for the query has been exceeded\n");
        return 0;
    }
    ans=(int *)malloc(q*sizeof(int));
    for(i=0;i<q;i++) {
        scanf("%d %d %d",&x,&y,&z);
        int da = abs(x - z), db = abs(y - z);
        if (lionandhyena(da, db)) ans[i] = 1;
        else if (lionandhyena(db, da)) ans[i] = 2;
        else ans[i] = 3;
    }
    for(i=0;i<q;i++) {
        if (ans[i] == 1) printf("Lion A\n");
        else if (ans[i] == 2) printf("Lion B\n");
        else printf("Hyena C\n");
    }
    return 0;
}
