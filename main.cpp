#include <iostream>
#include <stdio.h>
using namespace std;

#define  ll long long

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
const int bi = 18;
ll INF = 1LL << 60;
int n, m;
int mod = 1000000007;
ll dp[N][2];
int f[N];
ll diff[N][2];
int head[N], point[N * 2], nxt[N * 2];
ll value[N];
ll ct[N][bi][2][2];
int cur;
int depth[N];


bool contain(int set, int i);

void addEdge(int u, int v) {
    point[++cur] = v;
    nxt[cur] = head[u];
    head[u] = cur;
}

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void dfs(int u, int dep, int fa) {
    depth[u] = dep;
    f[u] = fa;
    ll sum1 = 0;
    ll sumMin = 0;
    for (int e = head[u]; e; e = nxt[e]) {
        int v = point[e];
        if (v == fa) continue;
        dfs(v, dep + 1, u);
        sum1 += dp[v][1];
        sumMin += min(dp[v][0], dp[v][1]);
    }
    dp[u][1] = value[u] + sumMin;
    dp[u][0] = sum1;
}

void dfs2(int u, int fa) {
    if (fa != 0) {
        ct[u][0][0][0] = 1;
    }

    for (int i = 0; i < bi; i++) {

    }
}


int main() {
    string str;
    cin>>n>>m>>str;
    for (int i = 1; i <= n; i++) {
        int v = read();
        value[i] = v;
    }

    for (int i = 1; i < n; i++) {
        int u = read();
        int v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 0; i < N; i++) for (int j = 0; j < 18; j++) for (int k = 0; k < 2; k++){
        ct[i][j][k][0] = 1;
        ct[i][j][k][1] = 1;
    }
    dfs(1, 1, 0);

    for (int i = 0; i < m; i++) {
        int a = read();
        int av = read();
        int b = read();
        int bv = read();
        if (depth[a] < depth[b]) {
            swap(a, b);
            swap(av, bv);
        }
        if (av == 0 && bv == 0) {
            bool ok = true;
            for (int e = head[a];e;e=nxt[e]) {
                if (point[e] == b) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                cout << -1 << endl;
                continue;
            }
        }

        if (av == 1) {
            diff[a][0] = INF - value[a];
            diff[a][1] = 0;
        } else {
            diff[a][1] = INF - value[a];
            diff[a][0] = 0;
        }
        if (bv == 1) {
            diff[b][0] = INF - value[b];
            diff[b][1] = 0;
        } else {
            diff[b][1] = INF - value[b];
            diff[b][0] = 0;
        }

        int k = depth[a] - depth[b];
        int ca = a;
        int cb = b;
        for (int i = 0; i < k; i++) {
            int fa = f[ca];
            if (fa == cb) {
                diff[fa][0] = diff[ca][1] + diff[cb][0];
                diff[fa][1] = min(dp[ca][1] + diff[ca][1], dp[ca][0] + diff[ca][0]) - min(dp[ca][1], dp[ca][0]) + diff[cb][1];
            } else {
                diff[fa][0] = diff[ca][1];
                diff[fa][1] = min(dp[ca][1] + diff[ca][1], dp[ca][0] + diff[ca][0]) - min(dp[ca][1], dp[ca][0]);
            }
            ca = fa;
        }
        while (ca != cb) {
            int fa = f[ca];
            int fb = f[cb];
            if (fa == fb) {
                diff[fa][0] = diff[ca][1] + diff[cb][1];
                diff[fa][1] = min(dp[ca][1] + diff[ca][1], dp[ca][0] + diff[ca][0]) - min(dp[ca][1], dp[ca][0]) +
                        min(dp[cb][1] + diff[cb][1], dp[cb][0] + diff[cb][0]) - min(dp[cb][1], dp[cb][0]);
            } else {
                diff[fa][0] = diff[ca][1];
                diff[fa][1] = min(dp[ca][1] + diff[ca][1], dp[ca][0] + diff[ca][0]) - min(dp[ca][1], dp[ca][0]);

                diff[fb][0] = diff[cb][1];
                diff[fb][1] = min(dp[cb][1] + diff[cb][1], dp[cb][0] + diff[cb][0]) - min(dp[cb][1], dp[cb][0]);
            }
            ca = fa;
            cb = fb;
        }
        while (f[ca] != 0) {
            int fa = f[ca];
            diff[fa][0] = diff[ca][1];
            diff[fa][1] = min(dp[ca][1] + diff[ca][1], dp[ca][0] + diff[ca][0]) - min(dp[ca][1], dp[ca][0]);
            ca = fa;
        }

        ll ans = min(dp[1][0] + diff[1][0], dp[1][1] + diff[1][1]);
        if (b == 1) {
            if (bv == 1) ans = dp[1][1] + diff[1][1];
            if (bv == 0) ans = dp[1][0] + diff[1][0];
        }
        if (ans >= INF) ans = -1;
        cout << ans << endl;
    }

    return 0;
}




bool contain(int set, int i) {
    return (set & (1 << i)) > 0;
}