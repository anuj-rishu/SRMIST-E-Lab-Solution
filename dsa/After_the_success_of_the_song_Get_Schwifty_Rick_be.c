#include <iostream>
#include <algorithm>
using namespace std;
const int MOD=1000000007,M=500000;int cnt[M+1],pow2[M+1],exact[M+1];
int main(){int n,x,mx=0;cin>>n;for(int i=0;i<n;i++){cin>>x;cnt[x]++;mx=max(mx,x);}
 pow2[0]=1;for(int i=1;i<=n;i++)pow2[i]=2LL*pow2[i-1]%MOD;
 long long ans=1;
 for(int d=mx;d>=1;d--){int c=0;for(int j=d;j<=mx;j+=d)c+=cnt[j];long long v=pow2[c]-1;
  for(int j=2*d;j<=mx;j+=d){v-=exact[j];}exact[d]=(v%MOD+MOD)%MOD;ans=(ans+1LL*d*exact[d])%MOD;
 }
 cout<<ans<<'\n';}
