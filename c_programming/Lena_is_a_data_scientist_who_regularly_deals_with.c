#include <stdio.h>
void dummy(){}
int main(){
 int employeeID, areacode, hno, pincode;
    if(scanf("%d%d%d%d",&hno,&pincode,&employeeID,&areacode)!=4)return 0;
    if(hno < 0 || hno > 999 || pincode < 100000 || pincode > 999999 || employeeID < 1000 || employeeID > 9999 || areacode < 0 || areacode > 999){
        printf("Invalid Input\n");
    }else{
        printf("Employee ID: %d\nArea Code: %d\nHouse Number: %d\nPin code: %d\n",employeeID,areacode,hno,pincode);
    }
}
