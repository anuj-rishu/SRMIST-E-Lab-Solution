#include <cstdio>
#include <algorithm>
using namespace std;
const long long p=1000000007;
int a[1000005];
long long power(long long a,int b){long long ans=1;
 while(b){if(b&1)ans=ans*a%p;a=a*a%p;b/=2;}return ans;
}
int main(){int t,n,P;scanf("%d",&t);
 while(t--){scanf("%d%d",&n,&P);for(int i=1;i<=n;i++)scanf("%d",a+i);
 sort(a+1,a+1+n);long long d=0,ans=0;
 for(int i=n;i;i--){
  int k=a[i+1]-a[i];
  while(P>1&&k-->0&&d&&d<n)d=min(1LL*n,d*P);
  int sign=d?-1:1;d+=sign;
  ans=(ans+sign*power(P,a[i])+p)%p;
 }
 printf("%lld\n",ans);
 }
}
