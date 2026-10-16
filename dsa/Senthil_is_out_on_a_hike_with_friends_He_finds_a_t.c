#include <stdio.h>
#include <stdlib.h>
void insertionSort(int *p,int n){
 for(int i=1;i<n;i++){int x=p[i],j=i-1;
  while(j>=0&&p[j]>x){p[j+1]=p[j];j--;}p[j+1]=x;
 }
}
int main(){
 int t,*n,**ans;scanf("%d",&t);
 n=(int *)malloc(t*sizeof(int));
 ans=(int * *)malloc(t*sizeof(int *));
 for(int i=0;i<t;i++){
  int count,a,b;scanf("%d%d%d",&count,&a,&b);
  if(a>b){int x=a;a=b;b=x;}
  n[i]=a==b?1:count;ans[i]=(int *)malloc(n[i]*sizeof(int));
  for(int j=0;j<n[i];j++)ans[i][j]=(count-1)*a+j*(b-a);
  insertionSort(ans[i],n[i]);
 }
 for(int i=0;i<t;i++){
  for(int j=0;j<n[i];j++)printf("%d ",ans[i][j]);
  printf("\n");free(ans[i]);
 }
 free(ans);free(n);return 0;
}
