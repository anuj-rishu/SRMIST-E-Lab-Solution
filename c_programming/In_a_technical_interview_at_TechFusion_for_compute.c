#include <stdio.h>
int main()
{
    int testnum1, testnum2; 
    int sum, sub, mult, mod;  
    float div;
    scanf("%d %d", &testnum1, &testnum2);
    if (testnum1 < 1 || testnum1 > 50 || testnum2 < 1 || testnum2 > 50)
    {
        printf("Invalid input");
    }
    else
    {
        sum = testnum1 + testnum2; sub = testnum1 - testnum2;
        mult = testnum1 * testnum2; div = (float)testnum1 / testnum2;
        mod = testnum1 % testnum2; printf("Addition: %d\n", sum);
        printf("Subtraction: %d\n", sub);
        printf("Multiplication: %d\n", mult);
        printf("Division: %.3f\n", div);
        printf("Modulus: %d", mod);
    }
    return 0;
}