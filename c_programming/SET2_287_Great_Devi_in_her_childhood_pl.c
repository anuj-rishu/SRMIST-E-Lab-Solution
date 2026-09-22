#include <stdio.h>

void dummy() {}

int main() {
    long long int n;
    scanf("%lld",&n);
    if (n> 10) {
        printf("Invaild\n");
        return 0;
    }
    long long int arr[n];
    long long int ans = 1;
    for(long long int i=0;i<n;i++) {
        scanf("%lld", &arr[i]);
        ans = (ans * (arr[i] + 1)) % 1000000007;
    }
    printf("%lld\n", ans - 1);
    return 0;
}
