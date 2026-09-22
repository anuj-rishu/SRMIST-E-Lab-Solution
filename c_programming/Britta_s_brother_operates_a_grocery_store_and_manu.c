#include <stdio.h>

struct groceryshop {
    char name[20];
    int qty;
    float price, gst;
} tax;

int main() {
    if (scanf("%19s", tax.name) != 1) {
        printf("Invalid input for name.\n");
        return 0;
    }
    if (scanf("%d", &tax.qty) != 1 || tax.qty <= 0) {
        printf("Invalid input for quantity.\n");
        return 0;
    }
    if (scanf("%f", &tax.price) != 1 || tax.price <= 0) {
        printf("Invalid input for price.\n");
        return 0;
    }

    tax.gst = tax.qty * tax.price;
    printf("GST: %.2f\nGST Amount: %.2f\nTotal including GST: %.2f\n", tax.gst, tax.gst * 0.14, tax.gst * 0.14 + tax.gst);

    return 0;
}
