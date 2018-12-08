#include <iostream>
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

const int N = 300010;
int INF = 1000000000;
int n, m;

struct Splay {
    int **ch, *key, *cnt, *sz, *f, *start, *end;
    ll *value;
//    int ch[N][2], key[N], cnt[N], sz[N], f[N];
    int tot, root;
    void Set(int n) {
        tot = root = 0;
        n++;
        ch = new int*[n];
        for (int i = 0; i < n; i++) {ch[i] = new int[2]; ch[i][0] = ch[i][1] = 0;}
        key = new int[n]; memset(key, 0, n * 4);
        cnt = new int[n]; memset(cnt, 0, n * 4);
        sz = new int[n]; memset(sz, 0, n * 4);
        f = new int[n]; memset(f, 0, n * 4);
        start = new int[n]; memset(start, 0, n * 4);
        end = new int[n]; memset(end, 0, n * 4);
        value = new ll[n]; memset(value, 0, n * 8);
    }
    void clear(int x) {
        ch[x][0] = ch[x][1] = f[x] = cnt[x] = sz[x] = key[x] = 0;
    }
    int get(int x) {
        return ch[f[x]][1] == x;
    }
    void update(int x) {
        if (x) {
            sz[x] = cnt[x];
            if (ch[x][0]) sz[x] += sz[ch[x][0]];
            if (ch[x][1]) sz[x] += sz[ch[x][1]];
        }
    }
    void rotate(int x) {
        int old = f[x]; int oldf = f[old];
        int which = get(x);
        ch[old][which] = ch[x][which^1];
        f[ch[old][which]] = old;
        ch[x][which^1] = old;
        f[old] = x;
        f[x] = oldf;
        if (oldf) {
            ch[oldf][ch[oldf][1] == old] = x;
        }
        update(old);
        update(x);
    }
    void splay(int x) {
        for (int fa; (fa = f[x]); rotate(x)) if (f[fa]) {
            rotate(get(fa) == get(x)? fa: x);
        }
        root = x;
    }
    void insert(int s, int e, ll v) {
        if (root == 0) {tot++; ch[tot][0] = ch[tot][1] = f[tot] = 0; key[tot] = s; cnt[tot]= sz[tot] = e - s; root = tot;
        start[tot] = s; end[tot] = e; value[tot] = v; return;}
        int now = root;
        int fa = 0;
        while (1) {
            if (key[now] == s) {
                cnt[now] ++;
                update(now);
                update(fa);
                splay(now);
                return;
            }
            fa = now;
            now = ch[now][key[now] < s];
            if (now == 0) {
                tot++;
                ch[tot][0] = ch[tot][1] = 0;
                f[tot] = fa;
                key[tot] = s;
                cnt[tot] = sz[tot] = e - s;
                ch[fa][key[fa] < s] = tot;
                start[tot] = s; end[tot] = e; value[tot] = v;
                update(fa);
                splay(tot);
                return;
            }
        }
    }
    int find(int v) {
        int now = root;
        int ans = 0;
        while (now) {
            if (v < key[now]) {
                now = ch[now][0];
            } else {
                ans += ch[now][0]?sz[ch[now][0]]:0;
                if (start[now] <= v && v < end[now] ) {
                    splay(now);
                    return ans + 1 + v - start[now];
                }
                ans += cnt[now];
                now = ch[now][1];
            }
        }
        return 0;
    }
    pii findx(int x) {
        int now = root;
        while (1) {
            if (ch[now][0] && x <= sz[ch[now][0]]) {
                now = ch[now][0];
            } else {
                x -= ch[now][0]?sz[ch[now][0]]:0;
                if (cnt[now] >= x) {
                    return mp(now, x);
                }
                x -= cnt[now];
                now = ch[now][1];
            }
        }
    }
    int pre() {
        int now = ch[root][0];
        while (ch[now][1]) now = ch[now][1];
        return now;
    }
    void del(int v) {
        int whatever = find(v);
       // if (cnt[root] > 1) {cnt[root]--;update(root);return;}
        if (!ch[root][0] && !ch[root][1]) {clear(root);root = 0;return;}
        else if (!ch[root][0]) {
            int oldroot = root;
            root = ch[oldroot][1];
            f[root] = 0;
            clear(oldroot);
            return;
        } else if (!ch[root][1]) {
            int oldroot = root;
            root = ch[oldroot][0];
            f[root] = 0;
            clear(oldroot);
            return;
        } else {
            int leftbig = pre();
            int oldroot = root;
            splay(leftbig);
            ch[root][1] = ch[oldroot][1];
            f[ch[root][1]] = root;
            clear(oldroot);
            update(root);
            return;
        }
    }
};
Splay s[N];
int size[N];
int qx[N], qy[N];
int idx[N];

int main() {
    //freopen("/Users/mobike/Downloads/testdata.in", "r", stdin);

    n = read();
    m = read();
    int q = read();
    memset(size, 0, sizeof(size));
    memset(idx, 0, sizeof(idx));
    for (int i = 0; i < q; i++) {
        int x = read();
        int y = read();
        qx[i] = x;
        qy[i] = y;
        if (y < m) size[x] ++;
    }
    for (int i = 1; i <= n; i++) {
        s[i].Set(size[i] * 3 + 1);
        s[i].insert(idx[i], idx[i] + m - 1, (ll)(i-1) * m + 1);
        idx[i] += m - 1;
    }
    s[n+1].Set(q + n);
    for (int i = 1; i <= n; i++) {
        s[n+1].insert(idx[n+1], ++idx[n+1], (ll)i * m);
    }
    for (int t = 0; t < q; t++) {
        int x = qx[t], y = qy[t];
        if (y <= m - 1) {
            pii px = s[x].findx(y);
            int now = px.first;
            int cnt = px.second;
            int start = s[x].start[now];
            int end = s[x].end[now];
            ll value = s[x].value[now];
            ll outValue = s[x].value[now] + (cnt - 1);
            printf("%lld\n", outValue);
            s[x].del(s[x].start[now]);
            if (cnt > 1) {
                s[x].insert(start, start + cnt - 1, value);
            }
            if (cnt < end - start) {
                s[x].insert(start + cnt, end, value + cnt);
            }

            pii pn = s[n+1].findx(x);
            now = pn.first;
            cnt = pn.second;
            start = s[n+1].start[now];
            end = s[n+1].end[now];
            value = s[n+1].value[now];
            s[n+1].del(start);
            s[x].insert(idx[x], ++idx[x], value);
            s[n+1].insert(idx[n+1], ++idx[n+1], outValue);
        } else {
            pii pairn = s[n+1].findx(x);
            int now = pairn.first;
            int start = s[n+1].start[now];
            int end = s[n+1].end[now];
            ll value = s[n+1].value[now];
            printf("%lld\n", value);
            s[n+1].del(start);
            s[n+1].insert(idx[n+1], ++idx[n+1], value);
        }
    }
    return 0;
}
