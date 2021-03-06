﻿#include "stdafx.h"

#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <stdio.h>
#include <unordered_map>
#include <cmath>
#include <iterator>

using namespace std;

#define ll long long
#define mp make_pair
#define pii pair<int, int>
int ans;

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
	return f == 1 ? res : -res;
}

const int N = 300010;
const int M = N << 1;
int INF = 1000000000;
int n, m;
int a[N], b[N], c[N], p[N];
int head[N], to[M], nxt[M], tot;
int level[N], fa[N], siz[N], son[N];
int top[N], id[N], rak[N], cur;

void addEdge(int x, int y) {
	++tot;
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}

void dfs1(int x, int f, int d) {
	fa[x] = f;
	level[x] = d;
	siz[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == f) continue;
		dfs1(to[i], x, d + 1);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
	}
}
void dfs2(int x, int tp) {
	cur++;
	id[x] = cur;
	rak[id[x]] = x;
	top[x] = tp;
	if (!son[x]) return;
	dfs2(son[x], tp);
	for (int i = head[x]; i; i = nxt[i]) {
		if (to[i] == fa[x] || to[i] == son[x]) continue;
		dfs2(to[i], to[i]);
	}
}


int main() {
	//freopen("C:/Users/user/Downloads/testdata.in", "r", stdin);
	n = read(); m = read();
	for (int i = 0; i < n; i++) {
		a[i] = read();
		b[i] = read();
		c[i] = read();
		addEdge(a[i], b[i]);
		addEdge(b[i], a[i]);
	}
	int root = rand() % n + 1;
	dfs1(root, 0, 1);
	dfs2(root, root);

	//system("pause");
	return 0;
}