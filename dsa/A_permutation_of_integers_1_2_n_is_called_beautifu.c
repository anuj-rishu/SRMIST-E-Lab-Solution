#include <stdio.h>

#define MOD 1000000007LL
typedef long long ll;

ll a[1005];

int main(){
    int n, k;
    if(scanf("%d", &n) != 1) return 0;
    a[0] = 1;
    a[1] = 1;
    for(k=2;k<=n;k++){
        if(k < 4) a[k] = 0;
        else {
            ll val = ((k + 1) * a[k - 1] - (k - 2) * a[k - 2] - (k - 5) * a[k - 3] + (k - 3) * a[k - 4]) % MOD;
            val %= MOD;
            if(val < 0) val += MOD;
            a[k] = val;
        }
    }
    printf("%lld\n", a[n]);
    return 0;
}
