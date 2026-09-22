#include <stdio.h>

int main() {
    int people_age,weight;
    scanf("%d%d", &people_age, &weight);
    if (people_age <= 11 || people_age >= 40 || weight <= 23 || weight >= 90)
        printf("Invalid input.\n");
    else if (people_age > 18 && weight > 40)
        printf("Eligible for Donation\n");
    else
        printf("Not Eligible for Donation\n");
}
