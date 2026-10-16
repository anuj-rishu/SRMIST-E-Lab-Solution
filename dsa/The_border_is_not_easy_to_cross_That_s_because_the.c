#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){int T;cin>>T;while(T--){int n;cin>>n;string s;for(int i=0,x;i<n;i++){cin>>x;s+=char('0'+x);}
 vector<vector<char>> B(n+1,vector<char>(n+1)),C=B;
 for(int len=1;len<=n;len++)for(int i=0;i+len<=n;i++){int j=i+len;
  if(len==1&&s[i]=='2')C[i][j]=1;
  if(len==3&&s[i]=='1'&&s[i+1]=='2')C[i][j]=1;
  if(len>=2&&s[i]=='2'&&B[i+1][j])B[i][j]=1;
  if(len>=5&&s[i]=='1'&&s[i+2]=='3'&&C[i+4][j])B[i][j]=1;
  if(len>=3&&s[i]=='3')for(int k=i+2;k<j;k++)if(B[i+1][k]&&C[k][j]){C[i][j]=1;break;}
 }
 if(n==1||B[0][n]||C[0][n])cout<<1<<'\n';else {cout<<0<<'\n';}continue;}}
