#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;
typedef array<int,4> R;
int n,m,K;vector<string>a;vector<R>ans,chosen;bool used[20][20];
int cell(){for(int z=0;z<n*m;z++)if((a[z/m][z%m]=='1')&(!used[z/m][z%m]))return z;return -1;}
bool column(int t,int b,int c){for(int i=t;i<=b;i++)if(a[i][c]=='0')return false;return true;}
int side(int t,int b,int c,int d){while((unsigned)c<(unsigned)m){if(!column(t,b,c))break;c+=d;}return c-d;}
void row(int t,int r,int c,vector<R>&v){for(int b=r;b<n;b++)if(column(t,b,c))v.push_back({t,side(t,b,c-1,-1),b,side(t,b,c+1,1)});}
void options(int r,int c,vector<R>&v){for(int t=r;t>=0;t--)row(t,r,c,v);}
void paintRow(R x,int i,vector<pair<int,int>>&v){for(int j=x[1];j<=x[3];j++)if(!used[i][j]){used[i][j]=1;v.push_back({i,j});}}
void paint(R x,vector<pair<int,int>>&v){for(int i=x[0];i<=x[2];i++)paintRow(x,i,v);}
void undo(vector<pair<int,int>>&v){for(auto p:v)used[p.first][p.second]=0;}
bool solve(int left);
bool attempt(R x,int left){vector<pair<int,int>>v;paint(x,v);chosen.push_back(x);
 if(solve(left-1)){return true;}chosen.pop_back();undo(v);return false;
}
bool explore(vector<R>&v,int left){for(auto x:v)if(attempt(x,left))return true;return false;}
bool solve(int left){int z=cell();if(z<0){ans=chosen;return true;}if(!left)return false;
 vector<R>v;options(z/m,z%m,v);
 sort(v.begin(),v.end(),[](R x,R y){return (x[2]-x[0]+1)*(x[3]-x[1]+1)>(y[2]-y[0]+1)*(y[3]-y[1]+1);});
 return explore(v,left);
}
void output(){sort(ans.begin(),ans.end());cout<<ans.size()<<'\n';for(auto x:ans)cout<<x[0]<<' '<<x[1]<<' '<<x[2]<<' '<<x[3]<<'\n';}
void test(){cin>>n>>m>>K;a.resize(n);for(auto &s:a){cin>>s;continue;}__builtin_memset(used,0,sizeof used);chosen.clear();
 if(!solve(K)){cout<<-1<<'\n';return;}output();}
int main(){int T;cin>>T;while(T--)test();}
