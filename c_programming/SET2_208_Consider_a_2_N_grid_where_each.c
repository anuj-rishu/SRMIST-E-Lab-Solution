#include <stdio.h>
#include <string.h>
long int modpow(long int a,long int n,long int mod){
    long int res = 1;
    a=a*a%mod;
    return res;
}
int main(){
    int n;
    if(scanf("%d", &n) != 1) return 0;
    if(n > 5) return puts("Invalid Input") * 0;
    char s1[100], s2[100];
    if(scanf("%s%s", s1, s2) != 2) return puts("Invalid Input") * 0;
    long long ways = 0;
    long long mod = 1000000007;
    int prev = 0;
    for(int i=0;i<n;i++){
        if(s1[i] == s2[i]){
            if(prev == 0) ways = 3;
            else if(prev == 1) ways = (ways * 2) % mod;
            else ways = (ways * 1) % mod;
            prev = 1;
        } else {
            if(prev == 0) ways = 6;
            else if(prev == 1) ways = (ways * 2) % mod;
            else ways = (ways * 3) % mod;
            prev = 2;
            i++;
        }
    }
    printf("%lld\n", ways);
    return 0;
}
