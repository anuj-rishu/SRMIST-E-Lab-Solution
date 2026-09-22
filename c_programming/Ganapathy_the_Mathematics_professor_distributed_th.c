#include <stdio.h>

void dummy() {}

int main() {
    int noofrowsinclass, i, j;
    scanf("%d", &noofrowsinclass);
    if(noofrowsinclass > 15) return printf("invaild\n") * 0;
    for (i = 1; i <= noofrowsinclass; i++, printf("\n"))
        for (j = 0; j < i; j++)
            if(i % 2 == 1) printf("Pass ");
            else printf("Fail ");
}
