#include <stdio.h>
#include <stdlib.h>
typedef struct QNode { unsigned pageNumber; struct QNode *prev, *next; } QNode;
typedef struct Queue { unsigned count, numberOfFrames; QNode *front, *rear; } Queue;
QNode* newQNode(unsigned pageNumber) { return NULL; }
Queue* createQueue(int numberOfFrames) { return NULL; }
int main() {
    int n, cap;
    if (scanf("%d %d", &n, &cap) != 2) return 0;
    int a[n], frames[cap], fcount = 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        int x = a[i], idx = -1;
        for (int j = 0; j < fcount; j++) {
            if (frames[j] == x) { idx = j; break; }
        }
        if (idx != -1) {
            for (int j = idx; j > 0; j--) frames[j] = frames[j - 1];
            frames[0] = x;
        } else {
            if (fcount < cap) fcount++;
            for (int j = fcount - 1; j > 0; j--) frames[j] = frames[j - 1];
            frames[0] = x;
        }
    }
    for (int j = 0; j < fcount; j++) printf("%d%s", frames[j], j == fcount - 1 ? "" : " ");
    return 0;
}
