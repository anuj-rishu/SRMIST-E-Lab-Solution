#include <stdio.h>

int main() {
    int prodid,billid,quantity;
    float price,totprice;
    scanf("%d", &billid);
    scanf("%d", &prodid);
    scanf("%f", &price);
    scanf("%d", &quantity);
    if(billid<=999||billid>=10001||prodid<=999||prodid>=10001||price<=9||price>=51||quantity<=0||quantity>=501) {
        printf("Invalid Input\n");
        return 0;
    }
    totprice=price*quantity;
    printf("%.2f\n", totprice);
    return 0;
}
