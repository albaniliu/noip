

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

const int N = 100;
const int mod = 1000000007;

struct Matrix {
    int n;
    ll mat[N][N];

    Matrix(int _n, ll diag): n(_n) {
        memset(mat, 0 ,sizeof(mat));
        for (int i = 0; i < n; i++) {
            mat[i][i] = diag;
        }
    }

    Matrix(const Matrix &c) {
        n = c.n;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            mat[i][j] = c.mat[i][j];
    }

    Matrix operator * (const Matrix &a) const {
        Matrix res(n , 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    res.mat[i][j] += mat[i][k] * a.mat[k][j];
                    res.mat[i][j] %= mod;
                }
        return res;
    }

    Matrix pow(ll t) {
        Matrix base = Matrix(*this);
        Matrix ans = Matrix(n, 1);
        while (t) {
            if (t & 1) {
                ans = ans * base;
            }
            base = base * base;
            t >>= 1;
        }
        return ans;
    }
};