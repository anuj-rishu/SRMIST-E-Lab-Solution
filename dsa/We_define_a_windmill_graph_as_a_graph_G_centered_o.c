#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define matrix(ii) vector<vector<int>>
int down_[100005],up_[100005],parent_[100005];
void dfs(matrix(ii)& graph, int root, int father,int& depth){
 parent_[root]=father;depth=max(depth,down_[root]);
 for(int v:graph[root])if(v!=father)dfs(graph,v,root,depth);
}
int main(){int n;cin>>n;vector<vector<int>> g(n+1);for(int i=1,u,v;i<n;i++){cin>>u>>v;if(u>=1&&u<=n&&v>=1&&v<=n){g[u].push_back(v);g[v].push_back(u);}}
 vector<int> order,par(n+1),up(n+1),down(n+1);order.reserve(n);order.push_back(1);par[1]=-1;
 for(size_t i=0;i<order.size();i++)for(int v:g[order[i]])if(v!=par[order[i]]){par[v]=order[i];order.push_back(v);}
 for(int i=n-1;i>=0;i--)for(int v:g[order[i]])if(v!=par[order[i]])down[order[i]]=max(down[order[i]],1+down[v]);
 for(int u:order){int a=0,b=0;for(int v:g[u])if(v!=par[u]){int x=1+down[v];if(x>a){b=a;a=x;}else if(x>b)b=x;}
  for(int v:g[u])if(v!=par[u])up[v]=1+max(up[u],(1+down[v]==a?b:a));
 }
 int best=-1,who=0;for(int u=1;u<=n;u++)if(g[u].size()>=5){int d=max(down[u],up[u]);if(d>=3&&int(g[u].size())+d>best){best=g[u].size()+d;who=u;}}
 if(best<0)cout<<-1<<'\n';else cout<<best<<' '<<who<<'\n';}
