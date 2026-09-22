#include <stdio.h>
#include <stdlib.h>
int compare(const void *a,const void *b){return *(int*)a-*(int*)b;}
int b[400005],p[200005],v[400005],A[200005],B[200005],i,n,q,c,u;
char T[200005];
void update(int i,int n,int x){for(;i<=n;i+=i&-i)b[i]+=x;}
int Q(int i){int s=0;for(;i>0;i-=i&-i)s+=b[i];return s;}
int R(int x,int u){int l=0,r=u-1,m,a=-1;while(l<=r){m=(l+r)/2;if(v[m]<=x){a=m;l=m+1;}else r=m-1;}return a+1;}
int main(){
scanf("%d%d",&n,&q);
for(i=1;i<=n;i++){scanf("%d",&p[i]);v[c++]=p[i];}
for(i=0;i<q;i++){
scanf(" %c%d%d",&T[i],&A[i],&B[i]);
if(T[i]==33)v[c++]=B[i];else{v[c++]=A[i];v[c++]=B[i];}
}
qsort(v,c,sizeof(int),compare);
for(i=0;i<c;i++)if(!i||v[i]!=v[i-1])v[u++]=v[i];
for(i=1;i<=n;i++)update(R(p[i],u),u,1);
for(i=0;i<q;i++){
if(T[i]==33){if(p[A[i]])update(R(p[A[i]],u),u,-1);p[A[i]]=B[i];update(R(B[i],u),u,1);}
else printf("%d\n",Q(R(B[i],u))-Q(R(A[i]-1,u)));
}
}
