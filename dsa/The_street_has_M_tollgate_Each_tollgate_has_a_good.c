#include <cstdio>
int A[1000005];__int128 s1,s2,ans;
void print(__int128 x){if(x>=10)print(x/10);putchar(48+x%10);}
int main(){int n;scanf("%d",&n);
 for(int i=0;i<n;i++){scanf("%d",A+i);s1 = s1 + A[i];}
 for(int i=0;i<n-1;i++){
  s2 = s2 + A[i];if(s2*(s1-s2)>ans)ans=s2*(s1-s2);
 }
 print(ans);
}
