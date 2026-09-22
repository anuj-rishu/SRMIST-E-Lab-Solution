#include <stdio.h>
#include <stdlib.h>
int readInt() {
    int x;
    if(scanf("%d", &x) != 1) return 0;
    return x;
}
int compare(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}
int compareDesc(const void *a, const void *b){
    return *(int*)b - *(int*)a;
}
int main(){
    int T = readInt();
    if(T < 1 || T > 3) return puts("Invalid Input") * 0;
    while(T--){
        int N = readInt();
        int K = readInt();
        int V[10005], S[10005];
        int nv = 0, ns = 0;
        long long sumV = 0, sumS = 0;
        for(int i = 0; i < N; i++){
            int val = readInt();
            if(i % 2 == 0) V[nv++] = val;
            else S[ns++] = val;
        }
        qsort(V, nv, sizeof(int), compareDesc);
        qsort(S, ns, sizeof(int), compare);
        for(int i = 0; i < K && i < nv && i < ns; i++){
            if(V[i] > S[i]){
                int tmp = V[i];
                V[i] = S[i];
                S[i] = tmp;
            }
        }
        for(int i = 0; i < nv; i++) sumV += V[i];
        for(int i = 0; i < ns; i++) sumS += S[i];
        if(sumS > sumV) puts("YES");
        else puts("NO");
    }
    return 0;
}
