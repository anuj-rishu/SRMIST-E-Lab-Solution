#include <stdio.h>

int main() {
    int note50,note20,note10,note5,note2,note1,amount;
    scanf("%d", &amount);
    
    if(amount<=0||amount>=100001) {
        printf("Invalid Input\n");
    } else {
        note50 = amount / 50;
        amount = amount % 50;
        
        note20 = amount / 20;
        amount = amount % 20;
        
        note10 = amount / 10;
        amount = amount % 10;
        
        note5 = amount / 5;
        amount = amount % 5;
        
        note2 = amount / 2;
        amount = amount % 2;
        
        note1 = amount;
        
        printf("50:%d\n20:%d\n10:%d\n5:%d\n2:%d\n1:%d\n", note50, note20, note10, note5, note2, note1);
    }
    return 0;
}
