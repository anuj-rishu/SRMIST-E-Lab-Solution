#include <stdio.h>
int main(){int t;scanf("%d",&t);
 while(t>0){int m,d,e,f,ans=0;scanf("%d%d%d%d",&m,&d,&e,&f);
  int temp1=1,temp2=1,temp3=1;
  for(int i=1;i<=m;i++){
   temp1=(i%d==0);temp2=(i%e==0);temp3=(i%f==0);
   if(temp1+temp2+temp3==1)ans++;
  }
  printf("%d\n",ans);t--;
 }
}
