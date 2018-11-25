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

const int N = 5001;
int n, m;
vector<int> graph[N];
int low[N];
int mark[N];
bool visited[N];
int cnt;
bool canReturn;
vector<int> res;
stack<int> nextStack;
int parent[N];
int circle[N][2];
int circleSize;
set<int> deleted;

void dfs(int cur, int p) {
    mark[cur] = cnt++;
//    low[cur] = cnt++;
//
//    for (int i = 0; i < graph[cur].size(); i++) {
//        int next = graph[cur][i];
//        if (mark[next] == -1) {
//            dfs(next, cur);
//            low[cur] = min(low[cur], low[next]);
//        } else if (next != parent) {
//            low[cur] = min(low[cur], mark[next]);
//        }
//    }

    parent[cur] = p;
    for (int i = 0; i < graph[cur].size(); i++) {
        int next = graph[cur][i];
        if (next == p) continue;
        if (mark[next] != -1 && circleSize == 0) {
            circle[circleSize][0] = cur;
            circle[circleSize++][1] = next;
            int np = p;
            int ncur = cur;
            while (np != next && np != -1) {
                circle[circleSize][0] = ncur;
                circle[circleSize++][1] = np;
                ncur = np;
                np = parent[np];
            }
            if (np != next) {
                ncur = next;
                np = parent[next];
                while (np != -1) {
                    circle[circleSize][0] = ncur;
                    circle[circleSize++][1] = np;
                    ncur = np;
                    np = parent[np];
                }
            }
        } else {
            if (mark[next] == -1)
                dfs(next, cur);
        }
    }
}

//void solve(int cur) {
//    visited[cur] = true;
//    res.push_back(cur);
//    vector<int> child;
//    for (int i = 0; i < graph[cur].size(); i++) {
//        int next = graph[cur][i];
//        if (!visited[next]) child.push_back(next);
//    }
//    for (int i = 0; i < child.size(); i++) {
//        int next = child[i];
//        if (visited[next]) continue;
//        if (!nextStack.empty() && next < nextStack.top() && canReturn && low[next] < mark[cur] && i == child.size() - 1) {
//            canReturn = false;
//            return;
//        }
//        if (i < child.size() - 1) nextStack.push(child[i+1]);
//        solve(next);
//        if (i < child.size() - 1) nextStack.pop();
//    }
//}

void solve(int cur, vector<int>& list) {
    visited[cur] = true;
    list.push_back(cur);
    for (int i = 0; i < graph[cur].size(); i++) {
        int next = graph[cur][i];
        if (deleted.find(next) != deleted.end() && deleted.find(cur) != deleted.end()) continue;
        if (!visited[next]) solve(next, list);
    }
}

int main() {
    n = read();
    m = read();
    for (int i = 0; i < m; i++) {
        int u = read() - 1;
        int v = read() - 1;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        sort(graph[i].begin(), graph[i].end());
    }
    for (int i = 0; i < n; i++) mark[i] = -1;
    dfs(0, -1);
    canReturn = true;
    res.push_back(n);
    if (circleSize == 0) {
        vector<int> tmp;
        for (int i = 0; i < n; i++) visited[i] = false;
        solve(0, tmp);
        bool ok = true;
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i] < res[i]) {
                ok = true;
                break;
            } else if (tmp[i] > res[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            res.clear();
            for (int i = 0; i < tmp.size(); i++) res.push_back(tmp[i]);
        }
    } else {
        for (int k = 0; k < circleSize; k++) {
            int u = circle[k][0];
            int v = circle[k][1];
            deleted.insert(u);
            deleted.insert(v);
            vector<int> tmp;
            for (int i = 0; i < n; i++) visited[i] = false;
            solve(0, tmp);
            deleted.clear();

            if (tmp.size() != n) continue;
            bool ok = true;
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp[i] < res[i]) {
                    ok = true;
                    break;
                } else if (tmp[i] > res[i]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                res.clear();
                for (int i = 0; i < tmp.size(); i++) res.push_back(tmp[i]);
            }
        }
    }
    for (int i = 0; i < res.size(); i++) {
        printf("%d", res[i] + 1);
        if (i != res.size() - 1) printf(" ");
    }
    printf("\n");
}