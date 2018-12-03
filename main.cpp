#include <iostream>
#include <stdio.h>
#include <queue>
#include <set>
#include <cstring>
using namespace std;

#define ll long long
#define mp make_pair
#define pii pair<int, int>

int read() {
    int f = 1;
    int res = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f = -f;
    } while (ch < '0' || ch > '9');
    do {
        res = res * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return res * f;
}

const int N = 100010;
const int M = 200010;
int INF = 1 << 29;
int n, m, K;
int mod;
int head1[N], headn[N], start[M<<1], point[M<<1], nxt[M<<1], value[M<<1];
int tot;

int ct[N << 2];
int seg = 0;
int dist1[N], distn[N];
ll f[N][55];
bool in[N][55];

void initSeg() {
    memset(ct, 0, sizeof(ct));
    seg = 1;
    while (seg <= n) seg *= 2;
    seg--;
    ct[0] = N - 1;
}

void adjust(int x, int y) {
    x += seg;
    ct[x] = y;
    for (; distn[ct[x>>1]] > distn[ct[x]]; x>>=1) ct[x>>1] = y;
}
int comp(int x, int y) {
    return distn[x] < distn[y] ? x: y;
}
void remove(int x) {
    x += seg;
    ct[x] = 0;
    x >>= 1;
    for (;x;x>>=1) {
        ct[x] = comp(ct[x<<1] , ct[x << 1 |1]);
    }
}

void init() {
    initSeg();
    memset(f, 0, sizeof(f));
    memset(in, 0, sizeof(in));
    for (int i = 0; i <= n; i++) {
        distn[i] = INF;
        head1[i] = 0;
        headn[i] = 0;
    }
}

bool contain(int set, int i);

void addEdge(int u, int v, int va, int* head) {
    point[++tot] = v;
    start[tot] = u;
    nxt[tot] = head[u];
    head[u] = tot;
    value[tot] = va;
}

void dij() {
    distn[n] = 0;
    adjust(n, n);
    while (ct[1]) {
        int u = ct[1];
        for (int e = headn[u]; e; e = nxt[e]) {
            int v = point[e];
            int va = value[e];
            if (distn[u] + va < distn[v]) {
                distn[v] = distn[u] + va;
                adjust(v, v);
            }
        }
        remove(u);
    }
}

ll dfs(int x, int y) {
    if (in[x][y]) return -1;
    if (f[x][y]) return f[x][y];
    in[x][y] = true;
    if (x == n) f[x][y] = 1;
    for (int e = head1[x]; e; e= nxt[e]) {
        int v = point[e];
        int va = value[e];
        if (distn[v] + va <= distn[x] + y) {
            ll tmp = dfs(v, distn[x] + y - distn[v] - va);
            if (tmp == -1) return f[x][y] = tmp;
            f[x][y] += tmp;
        }
    }
    in[x][y] = false;
    f[x][y] %= mod;
    return f[x][y];
}

int main() {
    int T = read();

    for (int t = 0; t < T; t++) {
        n = read();
        m = read();
        K = read();
        mod = read();
        init();

        for (int i = 0; i < m; i++) {
            int u = read();
            int v = read();
            int c = read();
            addEdge(u, v, c, head1);
            addEdge(v, u, c, headn);
        }
        dij();
        ll ans = dfs(1, K);
        printf("%lld\n", ans);
    }

    return 0;
}




bool contain(int set, int i) {
    return (set & (1 << i)) > 0;
}