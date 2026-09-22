#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_digit(char *ip_str) {
    while (*ip_str) {
        if (*ip_str < '0' || *ip_str > '9') return 0;
        ip_str++;
    }
    return 1;
}

int is_valid_ip(char *ip_str) {
    char *ptr;
    int dots = 0;
    ptr = strtok(ip_str, ".");
    while (ptr) {
        int num = atoi(ptr);
        if (!valid_digit(ptr) || num > 255) return 0;
        dots++;
        ptr = strtok(NULL, ".");
    }
    return dots == 4;
}

int main() {
    int t;
    char str[100];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);
        if (is_valid_ip(str))
            printf("Valid\n");
        else
            printf("Invalid\n");
    }
    return 0;
}
