//
//

#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>
#include <cassert>
#include <bitset>
#include <iomanip>

typedef long long ll;
using namespace std;

struct BSGS {
    map<ll, ll> tab;
    ll qpow(ll a, ll b, ll p) {
        ll ans = 1, base = a;
        while (b) {
            if (b & 1) {
                ans = ans * base % p;
            }
            base = base * base % p;
            b >>= 1;
        }
        return ans;
    }

    ll bsgs(ll a, ll b, ll p) {
        ll u = (ll) sqrt(p) + 1;
        ll now = 1;
        for (ll i = 0; i <= u; i++) {
            ll tmp = b * now % p;
            if (!tab.count(tmp))
                tab[tmp] = i;
            now = now * a % p;
        }
        ll step = qpow(a, u, p);
        ll ans = 1;
        for (ll i = 0; i <= u; i++) {
            ans = ans * step % p;
            if (tab.count(ans)) {
                ll res = ((i+1) * u - tab[ans]) % p;
                return res;
            }
        }
        return -1;
    }
}bsgs;