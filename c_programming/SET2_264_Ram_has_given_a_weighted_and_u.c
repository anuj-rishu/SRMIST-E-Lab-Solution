#include <stdio.h>

#define MXV 1000
#define MXE 500000

int input[MXE][3];
int dist[MXV][MXV];

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main() {
    int V, E;
    if (scanf("%d%d", &V, &E) != 2) return 0;
    if (V < 2 || V > MXV || E < 0 || E > MXE) {
        return puts("Invalid Input") * 0;
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = 0;
        }
    }
    for (int i = 0; i < E; i++) {
        scanf("%d%d%d", &input[i][0], &input[i][1], &input[i][2]);
        int u = input[i][0];
        int v = input[i][1];
        int w = input[i][2];
        if (u < V && v < V) {
            dist[u][v] = max(dist[u][v], w);
            dist[v][u] = max(dist[v][u], w);
        }
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            if (dist[i][k] == 0) continue;
            for (int j = 0; j < V; j++) {
                int score = min(dist[i][k], dist[k][j]);
                if (score > dist[i][j]) {
                    dist[i][j] = score;
                }
            }
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) printf("0 ");
            else printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}
