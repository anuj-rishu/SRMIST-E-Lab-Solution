#include <stdio.h>
#include <string.h>

struct Attendance {
    char name[99],city[99];
} s[15];
int n,i,j;

void sort() {
    struct Attendance t;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (strcmp(s[i].name, s[j].name) > 0) {
                t=s[i];
                s[i] = s[j];
                s[j] = t;
            }
}

int main() {
    scanf("%d", &n);
    if (n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    for(i=0;i<n;i++)
        scanf("%s%s", s[i].name, s[i].city);
    sort();
    for(i=0;i<n;i++)
        printf("%s-%s\n", s[i].name, s[i].city);
}
