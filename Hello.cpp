#include "stdafx.h"

#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <stdio.h>

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
int n, m, v ,e;
int face[N];
char name[N][12];
int room[2][N];
double pro[N];
int table[V][V];
int dist[V][V];
double f[2][N][N];

double solve(int r, int index, int chnum) {
	if (index >= n-1) return 0;
	if (f[r][index][chnum] >= 0) return f[r][index][chnum];
	int roomStart = room[r][index];
	int roomEnd = room[0][index + 1];
	double ans = solve(0, index + 1, chnum);
	ans += dist[roomStart][roomEnd];
	if (chnum >= 1) {
		double tmp = ans * (1.0 - pro[index + 1]);
		double tans = solve(1, index + 1, chnum - 1);
		roomEnd = room[1][index + 1];
		tans += dist[roomStart][roomEnd];
		tans = tans * pro[index + 1];
		ans = min(ans, tans + tmp);
	}
	return f[r][index][chnum] = ans;
}

int main() {
	//freopen("C:/Users/user/Downloads/testdata.in", "r", stdin);

	scanf("%d %d %d %d", &n, &m, &v, &e);
	for (int i = 0; i < n; i++) {
		cin>>room[0][i];
	}
	for (int i = 0; i < n; i++) {
		cin>>room[1][i];
	}
	for (int i = 0; i < n; i++) {
		cin>>pro[i];
	}
	for (int i = 0; i <= v; i++) {
		for (int j = 0; j <= v; j++) {
			table[i][j] = INF;
		}
		table[i][i] = 0;
	}
	for (int i = 0; i < e; i++) {
		int u, v, w;
		cin>>u>>v>>w;
		table[u][v] = table[v][u] = min(table[u][v], w);
	}
	for (int i = 1; i <= v; i++) for (int j = 1; j <= v; j++) dist[i][j] = table[i][j];
	for (int k = 1; k <= v; k++) {
		for (int i = 1; i <= v; i++) for (int j = 1; j <= v; j++)
			dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	}
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) f[0][i][j] = f[1][i][j] = -1.0;
	double ans = solve(0, 0, m);
	if (m >= 1) {
		double tmp = ans * (1.0 - pro[0]);
		double tans = solve(1, 0, m - 1);
		tans = tans * pro[0];
		ans = min(ans, tmp + tans);
	}
	cout << ans << endl;
	system("pause");
	return 0;
}
