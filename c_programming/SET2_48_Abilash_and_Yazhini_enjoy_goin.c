#include <stdio.h>

int main() {
    int month;
    scanf("%d", &month);
    if (month >= 13 || month <= 0)
        printf("Invalid input.\n");
    else switch(month) {
        case 2: printf("28/29 days\n"); break;
        case 4: case 6: case 9: case 11: printf("30 days\n"); break;
        default: printf("31 days\n");
    }
}
