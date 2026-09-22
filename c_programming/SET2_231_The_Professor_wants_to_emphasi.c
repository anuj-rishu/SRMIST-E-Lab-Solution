#include <stdio.h>
typedef struct {
    int data[100];
    int f, r;
} queue;
void enqueue(int key,queue *q);
int dequeue(queue *q);
int front(queue *q);
int isEmpty(queue *q);
void enqueue(int key,queue *q){
    q->data[q->r++] = key;
}
int dequeue(queue *q){
    return q->data[q->f++];
}
int front(queue *q){
    return q->data[q->f];
}
int isEmpty(queue *q){
    return q->f == q->r;
}
int main(){
    int n;
    if(scanf("%d", &n) != 1) return 0;
    if(n < 1 || n > 10) return puts("Invaild.") * 0;
    queue q = {.f = 0, .r = 0};
    int ideal[100];
    for(int i = 0; i < n; i++){
        int x; scanf("%d", &x);
        enqueue(x, &q);
    }
    for(int i = 0; i < n; i++) scanf("%d", &ideal[i]);
    int t = 0, cur = 0;
    while(cur < n){
        t++;
        int val = dequeue(&q);
        if(val == ideal[cur]){
            cur++;
        } else {
            enqueue(val, &q);
        }
    }
    printf("%d\n", t);
    return 0;
}
