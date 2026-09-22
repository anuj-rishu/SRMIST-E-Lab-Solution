#include <stdio.h>
#include <math.h>

void dummy() {}

int main() {
    long int q,start,end;
    scanf("%ld",&q);
    if(q<=0||q>=100) return printf("Invalid Input\n") * 0;
    while (q--) {
        scanf("%ld %ld", &start, &end);
        printf("%ld\n", (long)sqrt(end) - (long)sqrt(start - 1));
    }
}
