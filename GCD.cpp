//
// Created by Mobike on 2019/5/31.
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


struct GCD {
    ll gcd(ll a, ll b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }

    ll ex_gcd(ll a, ll b, ll &x, ll &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        ll q = ex_gcd(b, a%b, y, x);
        y -= a / b * x;
        return q;
    }
}gcd;
