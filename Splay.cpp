
struct SplayTree {

	int f[MAXN], cnt[MAXN], ch[MAXN][2], size[MAXN], key[MAXN], sz, rt;

	void clear(int x)
	{
		f[x] = cnt[x] = ch[x][0] = ch[x][1] = size[x] = key[x] = 0;
	}

	bool get(int x)
	{
		return ch[f[x]][1] == x;
	}

	void pushup(int x)
	{
		if (x)
		{
			size[x] = cnt[x];
			if (ch[x][0]) size[x] += size[ch[x][0]];
			if (ch[x][1]) size[x] += size[ch[x][1]];
		}
	}

	void rotate(int x)
	{
		int old = f[x], oldf = f[old], which = get(x);
		ch[old][which] = ch[x][which ^ 1]; f[ch[old][which]] = old;  //这两句的意思是：
																	 //我的儿子过继给我的爸爸；同时处理父子两个方向上的信息
		ch[x][which ^ 1] = old; f[old] = x;
		//我给我爸爸当爹，我爸爸管我叫爸爸
		f[x] = oldf;//我的爷爷成了我的爸爸
		if (oldf) ch[oldf][ch[oldf][1] == old] = x;
		pushup(old); pushup(x);//分别维护信息 
	}

	void splay(int x)
	{
		for (int fa; fa = f[x]; rotate(x))
			if (f[fa])
				rotate((get(x) == get(fa)) ? fa : x);//如果祖父三代连城一条线，就要从祖父哪里rotate 
		rt = x;
	}

	void insert(int x)//x为权值 
	{
		if (rt == 0)
		{
			sz++; key[sz] = x; rt = sz;
			cnt[sz] = size[sz] = 1;
			f[sz] = ch[sz][0] = ch[sz][1] = 0;
			return;
		}
		int now = rt, fa = 0;
		while (1)
		{
			if (x == key[now])//这个数在树中已经出现了 
			{
				cnt[now]++; pushup(now); pushup(fa); splay(now); return;
			}
			fa = now; now = ch[now][key[now]<x];
			if (now == 0)
			{
				sz++;
				size[sz] = cnt[sz] = 1;
				ch[sz][0] = ch[sz][1] = 0;
				ch[fa][x>key[fa]] = sz;//根据加入点的顺序重新标号 
				f[sz] = fa;
				key[sz] = x;
				pushup(fa); splay(sz); return;
			}
		}
	}

	int rnk(int x)//查询x的排名
	{
		int now = rt, ans = 0;
		while (1)
		{
			if (x<key[now]) now = ch[now][0];
			else
			{
				ans += size[ch[now][0]];
				if (x == key[now])
				{//此时x和树中的点重合，树中不允许有两个相同的点 
					splay(now); return ans + 1;
				}
				ans += cnt[now];
				now = ch[now][1];//到达右孩子处 
			}
		}
	}

	int kth(int x)
	{//查询排名为x的数 
		int now = rt;
		while (1)
		{
			if (ch[now][0] && x <= size[ch[now][0]])
				now = ch[now][0];
			else
			{
				int temp = size[ch[now][0]] + cnt[now];
				if (x <= temp)
					return key[now];
				x -= temp; now = ch[now][1];
			}
		}
	}

	int pre()//由于进行splay后，x已经到了根节点的位置 
	{//所以只要寻找左右子树最左边（或最右边的）数 
		int now = ch[rt][0];
		while (ch[now][1]) now = ch[now][1];
		return now;
	}

	int next()
	{
		int now = ch[rt][1];
		while (ch[now][0]) now = ch[now][0];
		return now;
	}

	void del(int x)
	{
		rnk(x);
		if (cnt[rt]>1) { cnt[rt]--; pushup(rt); return; }//有多个相同的数 
		if (!ch[rt][0] && !ch[rt][1]) { clear(rt); rt = 0; return; }
		if (!ch[rt][0]) {
			int oldrt = rt; rt = ch[rt][1]; f[rt] = 0; clear(oldrt); return;
		}
		else if (!ch[rt][1]) {
			int oldrt = rt; rt = ch[rt][0]; f[rt] = 0; clear(oldrt); return;
		}
		int oldrt = rt; int leftbig = pre();
		splay(leftbig);
		ch[rt][1] = ch[oldrt][1];
		f[ch[oldrt][1]] = rt;
		clear(oldrt);
		pushup(rt);
	}
}spt;