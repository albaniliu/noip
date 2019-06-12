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

const int N = 1000;

struct BIT {
    int n;
    ll arr[N];
    void init(int n_) {
        n = n_;
        memset(arr, 0, sizeof(arr));
    }
    void add(int x, int v) {
        for (;x<= n; x += x&-x) arr[x] += v;
    }
    ll get(int x) {
        ll ans = 0;
        for (;x; x -= x&-x) ans += arr[x];
        return ans;
    }
} bit;