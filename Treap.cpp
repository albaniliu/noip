struct fhqTreap {
#define ls c[rt][0]
#define rs c[rt][1]
	int c[N][2], sz[N], val[N], ra[N], cnt, RT;
	int rand() {
		static int seed = 233;
		return seed = (int)seed * 482711LL % 2147483647;
	}
	int ne(int v) { sz[++cnt] = 1; val[cnt] = v; ra[cnt] = rand(); return cnt; }
	void pu(int rt) { sz[rt] = sz[ls] + sz[rs] + 1; }
	void sl(int rt, int k, int &x, int &y) {
		if (!rt) { x = y = 0; return; }
		if (val[rt]>k)y = rt, sl(ls, k, x, ls);
		else x = rt, sl(rs, k, rs, y);
		pu(rt);
	}
	int mg(int x, int y) {
		if (!x || !y)return x + y;
		if (ra[x]<ra[y]) {
			c[x][1] = mg(c[x][1], y);
			pu(x);
			return x;
		}
		else {
			c[y][0] = mg(x, c[y][0]);
			pu(y);
			return y;
		}
	}
	void ins(int v) {
		int x, y;
		sl(RT, v, x, y);
		RT = mg(mg(x, ne(v)), y);
	}
	void del(int v) {
		int x, y, z;
		sl(RT, v, x, z);
		sl(x, v - 1, x, y);
		RT = mg(mg(x, mg(c[y][0], c[y][1])), z);
	}
	int kth(int rt, int k) {
		if (k <= sz[ls])return kth(ls, k);
		if (k == sz[ls] + 1)return rt;
		return kth(rs, k - sz[ls] - 1);
	}
	int frk(int v) {
		int x, y, t;
		sl(RT, v - 1, x, y);
		t = sz[x] + 1;
		RT = mg(x, y);
		return t;
	}
	int pre(int v) {
		int x, y, t;
		sl(RT, v - 1, x, y);
		t = val[kth(x, sz[x])];
		RT = mg(x, y);
		return t;
	}
	int nxt(int v) {
		int x, y, t;
		sl(RT, v, x, y);
		t = val[kth(y, 1)];
		RT = mg(x, y);
		return t;
	}
};


struct Treap {
	int tot, root;

	struct Treap_node {
		int rd, sz, ch[2], cnt, key;
	}t[N];

	Treap() {
		tot = root = 0;
		memset(t, 0, sizeof(t));
	}
	//注意初始化

	void push_up(int p) {
		t[p].sz = t[p].cnt;
		t[p].sz += t[t[p].ch[0]].sz;
		t[p].sz += t[t[p].ch[1]].sz;
	}
	//更新节点大小

	void rotate(int &p, int dir) {
		//dir = 0 / 1 -> 右旋 / 左旋
		int s = t[p].ch[dir ^ 0];
		t[p].ch[dir ^ 0] = t[s].ch[dir ^ 1];
		t[s].ch[dir ^ 1] = p;
		push_up(p);
		push_up(s);
		p = s;
	}
	//旋转

	void Insert(int &p, int key) {
		if (p == 0) {
			p = ++tot;
			t[p].sz = 1;
			t[p].cnt = 1;
			t[p].key = key;
			t[p].rd = rand();
			return;
		}
		++t[p].sz;
		if (t[p].key == key) {
			++t[p].cnt;
		}
		else {
			int dir = key > t[p].key;
			Insert(t[p].ch[dir], key);
			if (t[p].rd > t[t[p].ch[dir]].rd) {
				rotate(p, dir);
			}
		}
	}
	//插入

	void Delete(int &p, int key) {
		if (p == 0) {
			return;
		}
		if (t[p].key == key) {
			if (t[p].cnt > 1) {
				--t[p].sz;
				--t[p].cnt;
			}
			else {
				if (t[p].ch[0] * t[p].ch[1] == 0) {
					//分支 < 2 
					p = t[p].ch[0] + t[p].ch[1];
				}
				else {
					if (t[p].ch[0] < t[p].ch[1]) {
						rotate(p, 0);
					}
					else {
						rotate(p, 1);
					}
					Delete(p, key);
				}
			}
		}
		else {
			--t[p].sz;
			Delete(t[p].ch[key > t[p].key], key);
		}
	}
	//删除

	int pre(int key) {
		int p = root, ans = 0;
		while (p != 0) {
			if (t[p].key < key) {
				ans = t[p].key;
				p = t[p].ch[1];
			}
			else {
				p = t[p].ch[0];
			}
		}
		return ans;
	}
	//前驱

	int nxt(int key) {
		int p = root, ans = 0;
		while (p != 0) {
			if (t[p].key > key) {
				ans = t[p].key;
				p = t[p].ch[0];
			}
			else {
				p = t[p].ch[1];
			}
		}
		return ans;
	}
	//后继

	int kth(int k) {
		int p = root;
		while (p != 0) {
			if (k <= t[t[p].ch[0]].sz) {
				p = t[p].ch[0];
			}
			else if (k > t[t[p].ch[0]].sz + t[p].cnt) {
				k -= t[t[p].ch[0]].sz + t[p].cnt;
				p = t[p].ch[1];
			}
			else {
				return t[p].key;
			}
		}
		return false;
	}
	//k大(返回的是第k大的键值)

	int get_rnk(int key) {
		int p = root, ans = 0;
		while (p != 0) {
			if (key < t[p].key) {
				p = t[p].ch[0];
			}
			else if (key > t[p].key) {
				ans += t[p].cnt;
				ans += t[t[p].ch[0]].sz;
				p = t[p].ch[1];
			}
			else {
				return ans + t[t[p].ch[0]].sz + 1;
			}
		}
		return false;
	}
	//求排名
}treap;