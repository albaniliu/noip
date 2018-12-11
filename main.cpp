#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <stdio.h>
#include <unordered_map>
#include <cmath>

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
    return f == 1?res:-res;
}

const int N = 2010;
const int V = 310;
int INF = 1000000000;
int n, m;
unordered_map<ll, int> dp;
double point[20][2];
double esp = 0.00000001;

bool contain(ll set, int i) {
    return set & (1LL << i);
}

int solve(ll set) {
    if (set == 0LL) return 0;
    if (dp.find(set) != dp.end()) {
        return dp[set];
    }
    if ((set & (set - 1)) == 0) return 1;
    int ans = 100;
    int u = 0;
    for (int i = 0; i < n; i++) {
        if (contain(set, i)) {
            u = i;
            break;
        }
    }
    ll nset = set - (1LL << u);
    ans = solve(nset) + 1;
    for (int i = u + 1; i < n; i++) if (contain(set, i)) {
        int v = i;
        double a = (point[v][1] * point[u][0] - point[u][1] * point[v][0]) / (point[v][0] * point[v][0] * point[u][0] - point[u][0] * point[u][0] * point[v][0]);
        if (a > 0) continue;
        double b = (point[u][1] - a * point[u][0] * point[u][0]) / point[u][0];
        nset = set - (1LL << v);
        for (int j = i + 1; j < n; j++) if (contain(set, j)) {
            if (abs(a * point[j][0] * point[j][0] + b * point[j][0] - point[j][1]) < esp) {
                nset = nset - (1LL << j);
            }
        }
        int tmp = solve(nset);
        ans = min(ans, tmp + 1);
    }
    dp[set] = ans;
    return ans;
}

int main() {
    //freopen("C:/Users/user/Downloads/testdata.in", "r", stdin);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >>n >> m;
        for (int i = 0; i < n; i++) {
            cin >> point[i][0] >> point[i][1];
        }
        int ans = solve((1LL << n) - 1);
        cout << ans << endl;
    }
    return 0;
}