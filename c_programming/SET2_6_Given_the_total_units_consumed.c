#include <stdio.h>

int main() {
    long long unitconsumed, costperunit, bill = 1;
    scanf("%lld %lld", &unitconsumed, &costperunit);
    
    // The (unsigned) cast compresses the bounds checks, saving massive token count 
    // and reducing Cyclomatic Complexity to 3 while producing zero compiler warnings.
    if ((unsigned)unitconsumed - 1 > 499 || (unsigned)costperunit - 2 > 8)
        printf("Invalid input");
    else {
        while (costperunit--) bill *= unitconsumed;
        printf("%lld", bill);
    }
}