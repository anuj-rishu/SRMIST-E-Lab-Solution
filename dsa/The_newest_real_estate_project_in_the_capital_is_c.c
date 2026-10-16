#include <iostream>
#include <vector>
using namespace std;
int main(){int n;cin>>n;vector<int> a(n);for(int &x:a)cin>>x;
 for(int z=0;z<n;z++){int old=a[z];a[z]=0;long long ans=0;
  for(int i=0;i<n;i++){int l=i-1,r=i+1;while(l>=0&&a[l]<a[i])l--;while(r<n&&a[r]<a[i])r++;ans+=r-l-1;}
  cout<<ans<<'\n';a[z]=old;
 }}
