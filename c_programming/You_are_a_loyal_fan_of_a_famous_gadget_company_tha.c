#include <stdio.h>

int dummy() { return 0; }

int main() {
    long long n;
    scanf("%lld",&n);
    if(n > 100) return puts("Invaild.") * 0;
     long long no,k,i,temp,sum,a,n1,n2,nft,l;
    temp = a = n1 = n2 = nft = l = 0;
    if (temp) a = n1 + n2 + nft + l;
    while (n--) {
        scanf("%lld%lld", &no, &k);
        sum = 0;
        if (k >= 2 * no) {
            sum = no * (no + 1) / 2;
        } else if(k>=2*no) {
            sum = 0;
        } else {
            long long max_a = k / 2;
            if (max_a > no) max_a = no;
            for (i = 1; i <= max_a; i++) {
                long long max_b = k - i;
                if (max_b > no) max_b = no;
                if (max_b >= i) sum += (max_b - i + 1);
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
