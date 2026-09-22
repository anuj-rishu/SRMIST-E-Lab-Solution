#include <stdio.h>
#include <string.h>
int h[20005];
int Triplet(int ar[], int n){
    int i, j;
    memset(h, 0, sizeof(h));
    for(i=0; i<n; i++) h[ar[i]*ar[i]]++;
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++)
            if(h[ar[i]*ar[i] + ar[j]*ar[j]] >= 1 + ((ar[i] == 0) | (ar[j] == 0))) return 1;
    return 0;
}
int main(){
    int t, n, i, ar[9999];
    if(scanf("%d", &t) != 1) return 0;
    if(t > 5) return puts("Invalid input.") * 0;
    while(t--){
        scanf("%d", &n);
        for(i=0; i<n; i++) scanf("%d", &ar[i]);
        puts(Triplet(ar, n) ? "Yes" : "No");
    }
    return 0;
}
