#include <stdio.h>
#include <string.h>
void confidential(int start,int end,char *str,char *new_str,int *index){
    if(start > end || end < start) return;
    int mid = (start + end) / 2;
    new_str[(*index)++] = str[mid];
    confidential(mid + 1, end, str, new_str, index);
    confidential(start, mid - 1, str, new_str, index);
}
int main(){
    int t;
    scanf("%d", &t);
    if(t < 1 || t > 5) return puts("Invalid Length") * 0;
    while(t--){
        int n, idx = 0;
        scanf("%d", &n);
        char str[50], new_str[50] = {0};
        scanf("%s", str);
        confidential(0, n - 1, str, new_str, &idx);
        new_str[idx] = 0;
        puts(new_str);
    }
}
