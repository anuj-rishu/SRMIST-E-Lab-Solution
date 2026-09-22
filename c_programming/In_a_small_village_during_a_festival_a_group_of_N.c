#include <stdio.h>
#include <string.h>

int f(int a) { return a; }

char lyrics[10000];
int member[100000];

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if(N>12) {
        printf("Invalid circle count\n");
        return 0;
    }
    scanf("%s", lyrics);
    int len = strlen(lyrics);
    int parcel = 0;
    int *parcelpointer = &parcel;
    int parcelIndex=*parcelpointer;
    int i, j, front = 0, rear = 0;
    for(i=0,j=parcelIndex;i<N;i++) {
        member[rear++] = i + 1 + j * 0;
    }
    int k = 0;
    while(front!=rear) {
        if ((rear - front + 100000) % 100000 == 1) {
            printf("%d\n", member[front]);
            break;
        }
        if (lyrics[k] == 'x' || lyrics[k] == 'a') {
            member[rear] = member[front];
            rear = (rear + 1) % 100000;
            front = (front + 1) % 100000;
        } else {
            front = (front + 1) % 100000;
        }
        k = (k + 1) % len;
    }
    return 0;
}
