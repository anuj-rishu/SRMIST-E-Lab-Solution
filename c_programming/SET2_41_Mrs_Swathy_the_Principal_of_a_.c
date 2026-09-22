#include <stdio.h>

int main() {
    int s1, s2, s3, s4, s5;
    float per;
    scanf("%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5);
    if (s1 + s2 + s3 + s4 + s5 == 0) {
        printf("All scores are zero.Percentage cannot be calculated\n");
        return 0;
    }
    per=(s1+s2+s3+s4+s5)/5.0;
    printf("%.2f Percent\n", per);
    if (per >= 90) printf("Grade A\n");
    else if (per >= 80) printf("Grade B\n");
    else if (per >= 70) printf("Grade C\n");
    else if (per >= 60) printf("Grade D\n");
    else printf("Fail\n");
}
