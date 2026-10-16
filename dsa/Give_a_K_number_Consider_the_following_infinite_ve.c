#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){long long K;int P;cin>>K>>P;vector<long long> p(P);for(auto &x:p)cin>>x;sort(p.begin(),p.end());
 long long ans=0;for(int i=0;i<P;i++){long long cost=(p[i]-1)%K+1-i;if(cost<1)cost=1;ans+=cost;}
 cout<<ans<<'\n';}
