#include <stdio.h>
void dummy(){}
int v[500005], l[500005], r[500005], sz, rt;
int op(int t, int x){
    int *c = &rt, a = -1;
    while(*c){
        if(v[*c] >= x) a = v[*c];
        if(t == 1 && v[*c] == x) return 0;
        c = (x < v[*c]) ? &l[*c] : &r[*c];
    }
    if(t == 1){ *c = ++sz; v[sz] = x; }
    return a;
}
int main(){
    int q, i, t, x;
    scanf("%*d%d", &q);
    for(i=0;i<q;i++){
        scanf("%d%d", &t, &x);
        t == 1 ? op(t, x) : printf("%d\n", op(t, x));
    }
    return 0;
}
