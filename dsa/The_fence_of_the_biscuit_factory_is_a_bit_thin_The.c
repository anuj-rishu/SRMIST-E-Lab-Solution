#include <stdio.h>

#define MAXN 100005
#define INF 1000000000000000000LL

typedef long long ll;

int n;
ll orig[MAXN];
ll tree_min[4 * MAXN];
int tree_pos[4 * MAXN];
ll tree_lazy[4 * MAXN];

void push_up(int node) {
    int left = node * 2, right = node * 2 + 1;
    if (tree_min[left] <= tree_min[right]) {
        tree_min[node] = tree_min[left];
        tree_pos[node] = tree_pos[left];
    } else {
        tree_min[node] = tree_min[right];
        tree_pos[node] = tree_pos[right];
    }
}

void apply_lazy(int node, ll val) {
    tree_min[node] += val;
    tree_lazy[node] += val;
}

void push_down(int node) {
    if (tree_lazy[node] != 0) {
        apply_lazy(node * 2, tree_lazy[node]);
        apply_lazy(node * 2 + 1, tree_lazy[node]);
        tree_lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    tree_lazy[node] = 0;
    if (l == r) {
        tree_min[node] = orig[l];
        tree_pos[node] = l;
    } else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        push_up(node);
    }
}

void update_add(int node, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        apply_lazy(node, val);
        return;
    }
    push_down(node);
    int mid = (l + r) / 2;
    if (ql <= mid) update_add(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update_add(node * 2 + 1, mid + 1, r, ql, qr, val);
    push_up(node);
}

void update_del(int node, int l, int r, int idx) {
    if (l == r) {
        tree_min[node] = INF;
        return;
    }
    push_down(node);
    int mid = (l + r) / 2;
    if (idx <= mid) update_del(node * 2, l, mid, idx);
    else update_del(node * 2 + 1, mid + 1, r, idx);
    push_up(node);
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &orig[i]);
    }
    build(1, 1, n);

    ll diff = 0;
    for (int day = 1; day <= n; day++) {
        ll min_val = tree_min[1];
        int pos = tree_pos[1];
        diff += (min_val - orig[pos]);
        update_del(1, 1, n, pos);
        if (pos > 1) {
            update_add(1, 1, n, 1, pos - 1, day);
        }
    }
    printf("%lld\n", diff);
    return 0;
}
