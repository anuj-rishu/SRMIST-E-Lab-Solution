#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[100005];int n,seen[100005],stamp,count_;
void dfs(int u){if(seen[u]==stamp)return;seen[u]=stamp;count_++;for(int v:g[u])dfs(v);}
int answer(){int best=n;for(stamp=1;stamp<=n;stamp++){count_=0;dfs(stamp);best=min(best,count_);}return best;}
int main(){int m,a,b;scanf("%d%d",&n,&m);while(m--){scanf("%d%d",&a,&b);g[a].push_back(b);}printf("%d\n",answer());}
