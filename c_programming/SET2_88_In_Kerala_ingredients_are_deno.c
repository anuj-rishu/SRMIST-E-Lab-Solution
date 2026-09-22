#include <stdio.h>
void dummy(){}
int main(){
    int t;
    if(scanf("%d",&t)!=1||t<1||t>2)return puts("Invaild Input")*0;
    while(t--){
        int n,i,ok=1;
        scanf("%d",&n);
        int arr[n];
        for(i=0;i<=n-1;i++)scanf("%d",&arr[i]);
        int cnt[1005]={0},seen[1005]={0},freq_used[1005]={0};
        for(i=0;i<n;i++){
            if(i>0&&arr[i]!=arr[i-1]){
                if(seen[arr[i]]){ok=0;break;}
            }
            seen[arr[i]]=1;
            cnt[arr[i]]++;
        }
        if(!ok){puts("NO");continue;}
        for(i=0;i<=1000;i++){
            if(cnt[i]>0){
                if(freq_used[cnt[i]]){ok=0;break;}
                freq_used[cnt[i]]=1;
            }
        }
        puts(ok?"YES":"NO");
    }
}
