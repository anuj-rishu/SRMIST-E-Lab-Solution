#include <set>
#include <algorithm>
#include <iostream>
using namespace std;
const int N=505;
int t,n,a[N],b[N],f,fd;
using S=multiset<pair<int,int>>;
bool equal(S as,S bs){return as==bs;}
S read(int*a){
 for(int i=0;i<n;i++)cin>>a[i];
 S s;
 for(int i=0;i<n;i++)s.insert(minmax(a[i],a[n-1-i]));
 return s;
}
int main(){cin>>t;while(t--){cin>>n;S as=read(a),bs=read(b);cout<<(equal(as,bs)?"yes":"no")<<'\n';}}
