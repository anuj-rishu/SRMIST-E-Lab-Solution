#include <stdio.h>
#include <string.h>

void dummy() {}

struct node {
    int val;
    struct node *next;
};
typedef struct node node;

node* delet(node* head) { return head; }
void print(node* head) {}
node* insert(node* head,int v) { return head; }

#define N 100005
#define M 200005

int head[N], to[M], nxt[M], ec = 0;
int dfn[N], low[N], timer = 0;
int st[N], top = 0, in_st[N];
int ans[N];

void add(int u, int v) {
    to[ec] = v; nxt[ec] = head[u]; head[u] = ec++;
}

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    st[top++] = u; in_st[u] = 1;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (!dfn[v]) {
            dfs(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_st[v]) {
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }
    if (low[u] == dfn[u]) {
        int count = 0;
        int idx = top - 1;
        while (idx >= 0) {
            count++;
            if (st[idx] == u) break;
            idx--;
        }
        while (top > 0) {
            int v = st[--top];
            in_st[v] = 0;
            if (count > 1) ans[v] = 1;
            if (v == u) break;
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i);
    for (int i = 1; i <= n; i++)
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    return 0;
}
