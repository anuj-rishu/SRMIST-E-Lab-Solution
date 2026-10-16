#include <stdio.h>
int main(){int m;scanf("%d",&m);int spiral[m][m];
 for(int i=0;i<m;i++)for(int j=0;j<m;j++)scanf("%d",&spiral[i][j]);
 for(int l=0;l<(m+1)/2;l++){
  int r=m-l-1;
  for(int j=l;j<=r;j++)printf("%d ",spiral[l][j]);
  for(int i=l+1;i<=r;i++)printf("%d ",spiral[i][r]);
  for(int j=r-1;j>=l;j--)printf("%d ",spiral[r][j]);
  for(int i=r-1;i>l;i--)printf("%d ",spiral[i][l]);
 }
}
