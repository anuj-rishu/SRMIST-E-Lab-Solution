#include <iostream>
#include <algorithm>
using namespace std;
long long a[100005],b[100005],v[100005],sum[100006];
int main(){
 int t;cin>>t;
 while(t--){
  long long n,ans=0;int m;cin>>n>>m;
  for(int i=0;i<m;i++){cin>>v[i]>>b[i];a[i]=v[i];}
  sort(a,a+m);sum[m+1]=0;
  for(int i=m;i>=1;i--)sum[i]=sum[i+1]+a[i-1];
  if(n<=m)ans=sum[m-n+1];
  for(int i=0;i<m;i++){
   int p=upper_bound(a,a+m,b[i])-a,c=m-p;
   if(c>=n)continue;
   long long value=sum[p+1];
   if(v[i]<=b[i]){value+=v[i];c++;}
   value+=(n-c)*b[i];
   ans=max(ans,value);
  }
  cout<<ans<<'\n';
 }
}
