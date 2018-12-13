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
int poke[14];
unordered_map<int, int> dp;

bool contain(int set, int i) {
    return (set & (1 << i)) > 0;
}

int getV(int set, int i) {
    int res = set & (3 << (i*2));
    return res;
}

int setV(int set, int i, int v) {
    int res = set - getV(set, i);
    res |= (v << (i * 2));
    return res;
}

int solve (int set) {
    if (set == 0) return 0;
    if (set & (set - 1) == 0) return 1;
    if (dp.find(set) != dp.end()) return dp[set];
    int start = 0;
    for (int i = 0; i <= 13; i++) if (getV(set, i) > 0) {
        start = i;
        break;
    }
    int num = getV(set, start);
    int nset = setV(set, start, num - 1);
    int ans = solve(nset);

    if (num >= 2) {
        int nset = setV(set, start, num - 2);
        ans = min(ans, solve(nset));
        for (int i = start + 1; i <= 13; i++) {
            
        }
    }
    return dp[set] = ans;
}

int main() {
    //freopen("C:/Users/user/Downloads/testdata.in", "r", stdin);
    int T = read();
    n = read();

    for (int t = 0; t < T; t++) {
        dp.clear();
        memset(poke, 0, sizeof(poke));
        for (int i = 0; i < n; i++) {
            int tmp = read();
            poke[tmp] ++ ;
            read();
        }
        int ans = poke[0] > 0?1:0;
        int set = 0;
        for (int i = 1; i <= 13; i++) if (poke[i] > 0) {
            set += poke[i] << (i * 2);
        }

        ans += solve(set);
        printf("%d\n", ans);
    }
    return 0;
}