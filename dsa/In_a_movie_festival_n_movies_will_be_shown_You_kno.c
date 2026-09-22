#include <stdio.h>
#define M 1000002
#define INF 1000005

int up[19][M];

void init(int n){
    for(int i=0; i<M; i++) up[0][i] = INF;
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        if(b < up[0][a]) up[0][a] = b;
    }
    for(int i=M-2; i>=0; i--){
        if(up[0][i+1] < up[0][i]) up[0][i] = up[0][i+1];
    }
}

void lift(){
    for(int j=1; j<19; j++){
        for(int i=0; i<M; i++){
            int nxt = up[j-1][i];
            up[j][i] = (nxt < M) ? up[j-1][nxt] : INF;
        }
    }
}

void query(){
    int a, b;
    scanf("%d%d", &a, &b);
    int ans = 0, cur = a;
    for(int j=18; j>=0; j--){
        if(up[j][cur] <= b){
            ans += (1 << j);
            cur = up[j][cur];
        }
    }
    printf("%d\n", ans);
}

int main(){
    int n, q;
    if(scanf("%d%d", &n, &q)==2){
        init(n);
        lift();
        while(q--) query();
    }
    return 0;
}
