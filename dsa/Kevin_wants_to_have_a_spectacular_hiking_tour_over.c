#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[100005],order;int h[100005],seen[100005],n,m,ans;
void dfs(int s,int st){vector<int> q(1,s);seen[s]=1;
 while(!q.empty()){int u=q.back();q.pop_back();ans=max(ans,h[u]-h[st]);
  for(int v:g[u])if(!seen[v]){seen[v]=1;q.push_back(v);}
 }}
void readCase(){int u,v;scanf("%d%d",&n,&m);ans=0;order.clear();
 for(int i=1;i<=n;i++){scanf("%d",h+i);g[i].clear();seen[i]=0;order.push_back(i);}
 while(m--){scanf("%d%d",&u,&v);if(u>=1&&u<=n&&v>=1&&v<=n)g[u].push_back(v);}
}
void run(){
 sort(order.begin(),order.end(),[](int a,int b){return h[a]<h[b];});
 for(int x:order){if(!seen[x])dfs(x,x);}printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--){readCase();run();}}
