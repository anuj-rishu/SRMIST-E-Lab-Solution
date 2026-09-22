#include <stdio.h>

long long tree[800005], lzC[800005], lzD[800005];
long long a[200005];

void build(int k,int l,int r){
    if(l==r){ tree[k]=a[l]; return; }
    int m=(l+r)/2;
    build(2*k,l,m);
    build(2*k+1,m+1,r);
    tree[k]=tree[2*k]+tree[2*k+1];
}

void push(int k, int l, int r){
    if(!lzC[k] && !lzD[k]) return;
    int m=(l+r)/2;
    long long lenL = m-l+1, lenR = r-m;
    lzC[2*k] += lzC[k];
    lzD[2*k] += lzD[k];
    tree[2*k] += lenL*lzC[k] + lenL*(lenL-1)/2*lzD[k];
    
    long long rightC = lzC[k] + lenL*lzD[k];
    lzC[2*k+1] += rightC;
    lzD[2*k+1] += lzD[k];
    tree[2*k+1] += lenR*rightC + lenR*(lenR-1)/2*lzD[k];
    
    lzC[k]=0; lzD[k]=0;
}

void update(int k, int l, int r, int ql, int qr, int origL){
    if(ql<=l && r<=qr){
        long long startVal = l - origL + 1;
        long long len = r - l + 1;
        lzC[k] += startVal;
        lzD[k] += 1;
        tree[k] += len * startVal + len*(len-1)/2;
        return;
    }
    push(k, l, r);
    int m=(l+r)/2;
    if(ql<=m) update(2*k, l, m, ql, qr, origL);
    if(qr>m) update(2*k+1, m+1, r, ql, qr, origL);
    tree[k]=tree[2*k]+tree[2*k+1];
}

long long query(int k, int l, int r, int ql, int qr){
    if(ql<=l && r<=qr) return tree[k];
    push(k, l, r);
    int m=(l+r)/2;
    long long ans=0;
    if(ql<=m) ans += query(2*k, l, m, ql, qr);
    if(qr>m) ans += query(2*k+1, m+1, r, ql, qr);
    return ans;
}

int main(){
    int n, q;
    if(scanf("%d%d", &n, &q)!=2) return 0;
    for(int i=1; i<=n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    while(q--){
        int type, ql, qr;
        if(scanf("%d%d%d", &type, &ql, &qr)!=3) break;
        if(qr > n) qr = n;
        if(type == 1) update(1, 1, n, ql, qr, ql);
        else printf("%lld\n", query(1, 1, n, ql, qr));
    }
    return 0;
}
