#include <stdio.h>
#define H 524288
typedef unsigned long long U;
typedef long long L;

U hK[H], u, v;
L hV[H], ans, W;
int du, dv, T, K;

int match(U i, U k){
    if(!hK[i]) return 1;
    return hK[i] == k;
}
U slot(U k){
    U i = (k * 11400714819323198485ULL) & (H - 1);
    while(!match(i, k)) i = (i + 1) & (H - 1);
    return i;
}
L getVal(U k){
    U i = slot(k);
    if(hK[i] == k) return hV[i];
    return 0;
}
void addVal(U k, L w){
    U i = slot(k);
    hK[i] = k;
    hV[i] += w;
}
int depth(U x){
    int d = 0;
    while(x > 1){ x /= K; d++; }
    return d;
}
void step_u(){
    if(T == 1) ans += 1 + getVal(u);
    if(T == 2) addVal(u, W);
    u /= K;
}
void step_v(){
    if(T == 1) ans += 1 + getVal(v);
    if(T == 2) addVal(v, W);
    v /= K;
}
void lift_u(){
    while(du > dv){ step_u(); du--; }
}
void lift_v(){
    while(dv > du){ step_v(); dv--; }
}
void meet(){
    while(u != v){ step_u(); step_v(); }
}
void run_q(){
    W = 0; ans = 0;
    scanf("%d%llu%llu", &T, &u, &v);
    if(T == 2) scanf("%lld", &W);
    du = depth(u); dv = depth(v);
    lift_u(); lift_v(); meet();
    if(T == 1) printf("%lld\n", ans);
}
int main(){
    int q;
    if(scanf("%d%d", &K, &q) == 2){
        while(q--) run_q();
    }
    return 0;
}
