#include <cstdio>
#include <unordered_map>
using namespace std;
int a[100005];
int main(){int t,n,q,i;scanf("%d",&t);
 while (t--){scanf("%d%d",&n,&q);unordered_map<int,int>cnt;cnt.reserve(n*2);
  for (i = 0; i < n; i++){scanf("%d",a+i);cnt[a[i]]++;}
  int kinds=cnt.size();
  while(q--){int pos,val;scanf("%d%d",&pos,&val);pos--;
   if(--cnt[a[pos]]==0)kinds--;
   if(cnt[val]++==0)kinds++;
   a[pos]=val;printf("%d\n",kinds+1);
  }
 }
}
