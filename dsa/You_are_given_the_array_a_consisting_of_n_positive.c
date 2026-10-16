#include <cstdio>
#include <algorithm>
using namespace std;
int main(){int t,n;scanf("%d",&t);
 while(t--){scanf("%d",&n);int a[n+1];
  for(int i=0;i<n;i++)scanf("%d",a+i);
  sort(a,a+n);bool ok=true;
  for(int i=1;i<n;i++)if(a[i]-a[i-1]>1)ok=false;
  puts(ok?"YES":"NO");
 }
}
