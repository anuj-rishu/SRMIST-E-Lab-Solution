#include <stdio.h>
#include <string.h>
#define min(string1,string2) string1<string2?string1:string2
int main(){
    int t,i,less1,l,less2,mid1,mid2,four1,four2,four,seven1,seven2,seven;
    if(scanf("%d", &t) != 1) return 0;
    if(t > 10) return puts("Invaild.") * 0;
    while(t--){
        char string1[50], string2[50];
        scanf("%s%s", string1, string2);
        l=strlen(string1);
        less1 = less2 = mid1 = mid2 = four1 = four2 = seven1 = seven2 = 0;
        for(i = 0; i < l; i++){
            if(string1[i] < '4') less1++;
            else if(string1[i] == '4') four1++;
            else if(string1[i] < '7') mid1++;
            else if(string1[i] == '7') seven1++;
            if(string2[i] < '4') less2++;
            else if(string2[i] == '4') four2++;
            else if(string2[i] < '7') mid2++;
            else if(string2[i] == '7') seven2++;
        }
        int avail2 = less2 + four2 + mid2;
        int avail1 = less1 + four1 + mid1;
        int p1 = min(seven1, avail2);
        seven1 -= p1; avail2 -= p1;
        int p2 = min(seven2, avail1);
        seven2 -= p2; avail1 -= p2;
        int p3 = min(seven1, seven2);
        seven = p1 + p2 + p3;
        int u2 = p1;
        int t2 = min(mid2, u2); mid2 -= t2; u2 -= t2;
        t2 = min(less2, u2); less2 -= t2; u2 -= t2;
        t2 = min(four2, u2); four2 -= t2; u2 -= t2;
        int u1 = p2;
        int t1 = min(mid1, u1); mid1 -= t1; u1 -= t1;
        t1 = min(less1, u1); less1 -= t1; u1 -= t1;
        t1 = min(four1, u1); four1 -= t1; u1 -= t1;
        int f1 = min(four1, less2);
        four1 -= f1; less2 -= f1;
        int f2 = min(four2, less1);
        four2 -= f2; less1 -= f2;
        int f3 = min(four1, four2);
        four = f1 + f2 + f3;
        for(i = 0; i < seven; i++) putchar('7');
        for(i = 0; i < four; i++) putchar('4');
        putchar('\n');
    }
    return 0;
}
