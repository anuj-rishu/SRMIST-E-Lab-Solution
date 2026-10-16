#include <stdio.h>
#include <string.h>

#define INF 1000000000

int N, M;
char grid[105][105];
int distR[105][105];
int distJ[105][105];

int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Point {
    int r, c;
} q[20005];

void bfs(int sR, int sC, int dist[105][105]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }
    int head = 0, tail = 0;
    dist[sR][sC] = 1;
    q[tail++] = (struct Point){sR, sC};

    while (head < tail) {
        struct Point cur = q[head++];
        for (int d = 0; d < 8; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (grid[nr][nc] != 'X' && dist[nr][nc] == INF) {
                    dist[nr][nc] = dist[cur.r][cur.c] + 1;
                    q[tail++] = (struct Point){nr, nc};
                }
            }
        }
    }
}

int main() {
    if (scanf("%d %d", &N, &M) != 2) return 0;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    int rR = -1, cR = -1, rJ = -1, cJ = -1;
    for (int i = 0; i < N; i++) {
        char line[205];
        if (!fgets(line, sizeof(line), stdin)) break;
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        for (int j = 0; j < M; j++) {
            char c = (j < len) ? line[j] : ' ';
            grid[i][j] = c;
            if (c == 'R') {
                rR = i;
                cR = j;
            } else if (c == 'J') {
                rJ = i;
                cJ = j;
            }
        }
    }

    bfs(rR, cR, distR);
    bfs(rJ, cJ, distJ);

    int bestT = INF, bestR = -1, bestC = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (distR[i][j] != INF && distR[i][j] == distJ[i][j]) {
                if (distR[i][j] < bestT) {
                    bestT = distR[i][j];
                    bestR = i + 1;
                    bestC = j + 1;
                }
            }
        }
    }

    printf("%d %d %d\n", bestT, bestR, bestC);
    return 0;
}
