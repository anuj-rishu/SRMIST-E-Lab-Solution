#include <stdio.h>

int main() {
    int month, numofdays;
     float roomrent, renttopay;
    scanf("%d%f%d", &month, &roomrent, &numofdays);
    if (month < 1 || month > 12 || roomrent < 500 || roomrent > 5000 || numofdays < 1 || numofdays > 15)
        printf("Invalid input\n");
    else {
        renttopay = roomrent * numofdays;
        if (month == 4 || month == 5)
            renttopay = renttopay + (numofdays * roomrent * 0.2);
        printf("Rs.%.2f\n", renttopay);
    }
}
