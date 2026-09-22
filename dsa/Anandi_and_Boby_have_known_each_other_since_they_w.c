#include <stdio.h>
#include <string.h>
void dummy(){}
int toInt(char a){ return (int)a; }
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    while(t--){
        char c1, c2;
        char s[100005];
        scanf(" %c %c", &c1, &c2);
        scanf("%s", s);
        int len = strlen(s);
        for(int i = 0; i < len; i++){
            if(s[i] == c1) s[i] = c2;
            else if(s[i] == c2) s[i] = c1;
        }
        printf("%s\n", s);
    }
    return 0;
}
