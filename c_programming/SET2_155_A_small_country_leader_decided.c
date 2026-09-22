#include <stdio.h>

union Citizen {
    int age;
};

int main() {
  union Citizen E;
    scanf("%d", &E.age);
  if(E.age<=1||E.age>=100)
        printf("Invalid\n");
    else
 if (E.age>18 && E.age<60)
        printf("Eligible\n");
    else
        printf("Not Eligible\n");
    return 0;
}
