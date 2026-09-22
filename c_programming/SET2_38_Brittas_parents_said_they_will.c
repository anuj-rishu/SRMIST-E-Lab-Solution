#include <stdio.h>

int main() {
    int day;
    scanf("%d", &day);
    const char *days[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    // if
    // else if
    // else
    day >= 1 && day <= 7 ? printf("%s\n", days[day]) : printf("Invalid Input\n");
    return 0;
}
