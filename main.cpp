#include "bits/stdc++.h"
#include <iostream>
using namespace std;

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

const int N = 256;
int M;
int n, m;
int mod = 1000000007;

bool contain(int set, int i);

void myMul(long long res[][N], long long A[][N], long long B[][N]) {
    for (int i = 0; i < M; i++) for (int j = 0; j < M; j++) {
            long long s = 0;
            for (int k = 0; k < M; k++) s += A[i][k] * B[k][j];
            res[i][j] = s % mod;
        }
}

void myPow(long long res[][N], long long table[][N], int m) {
    if (m == 1) {
        for (int i = 0; i < M; i++) for (int j = 0; j < M; j++) res[i][j] = table[i][j] % mod;
        return;
    }
    long long tmp[N][N];
    myPow(tmp, table, m / 2);
    for (int i = 0; i < M; i++) for (int j = 0; j < M; j++) {
        res[i][j] = tmp[i][j];
        tmp[i][j] = 0;
    }
    myMul(tmp, res, res);
    for (int i = 0; i < M; i++) for (int j = 0; j < M; j++) {
        res[i][j] = tmp[i][j];
        tmp[i][j] = 0;
    }
    if (m % 2 == 1) {
        myMul(tmp, res, table);
        for (int i = 0; i < M; i++) for (int j = 0; j < M; j++){
            res[i][j] = tmp[i][j];
            tmp[i][j] = 0;
        }
    }
}

int main() {
    cin>>n>>m;

    if (n > m) {
        int t = n;
        n = m;
        m = t;
    }
    M = (1 << n) | ((n-1) << n);
    for (int k = 0; k < n; k++) {
        
    }
    return 0;
}


bool contain(int set, int i) {
    return (set & (1 << i)) > 0;
}