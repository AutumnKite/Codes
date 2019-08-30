#include <cstdio>
#include <cctype>
int read(){
	int x = 0, f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
struct Splay{
	int cnt, rt, val[N], fa[N], son[N][2], sz[N], sum[N];
	int new_node(int x){
		return val[++cnt] = x, son[cnt][0] = son[cnt][1] = 0, sum[cnt] = 1, sz[cnt] = 1, cnt;
	}
	void update(int x){
		sz[x] = sz[son[x][0]] + sz[son[x][1]] + sum[x];
	}
	int dir(int x){
		return son[fa[x]][1] == x; 
	}
	void change(int x, int k, int y){
		son[x][k] = y, fa[y] = x;
	}
	void rotate(int x){
		int y = fa[x], d = dir(x);
		change(y, d, son[x][!d]), change(fa[y], dir(y), x), change(x, !d, y);
		update(y), update(x);
	}
	void splay(int x, int p){
		while (fa[x] != p){
			int y = fa[x];
			if (fa[y] == p) { rotate(x); break; }
			dir(y) == dir(x) ? rotate(y) : rotate(x);
			rotate(x);
		}
		if (!p) rt = x;
	}
	void Find(int x){
		int u = rt;
		if (!u) return;
		while (son[u][x > val[u]] && val[u] != x) u = son[u][x > val[u]];
		splay(u, 0);
	}
	int Next(int x, int q){ // q = 0(pre) or 1(next)
		Find(x);
		if (q && val[rt] > x || !q && val[rt] < x) return rt;
		for (int u = son[rt][!(q = !q)]; ; u = son[u][q]) if (!son[u][q]) return u;
	}
	void Insert(int x){
		int u = rt, v = 0;
		while (u && val[u] != x) v = u, u = son[u][x > val[u]];
		if (u) ++sum[u]; else u = new_node(x), fa[u] = v, v ? son[v][x > val[v]] = u : 0;
		splay(u, 0);
	}
	void Delete(int x){
		Find(x);
		if (!son[rt][0]) return --sum[rt] ? 0 : (fa[son[rt][1]] = 0, rt = son[rt][1]), (void)0;
		int y;
		for (int u = son[rt][0]; ; u = son[u][1]) if (!son[u][1]) { y = u; break; }
		--sum[rt] ? 0 : (splay(y, rt), son[y][1] = son[rt][1], fa[son[rt][1]] = y, fa[y] = 0, rt = y);
	}
	int Rank(int x){
		return Find(x), sz[son[rt][0]] + 1;
	}
	int Kth(int x){
		int u = rt;
		while (2333){
			if (x > sz[son[u][0]] + sum[u]) x -= sz[son[u][0]] + sum[u], u = son[u][1];
			else if (x <= sz[son[u][0]]) u = son[u][0];
			else return val[u];
		}
	}
}T;
int main(){
	T.Insert(-2147483647), T.Insert(2147483647);
	int n = read();
	while (n--){
		int opt = read(), x = read();
		if (opt == 1) T.Insert(x);
		if (opt == 2) T.Delete(x);
		if (opt == 3) printf("%d\n", T.Rank(x) - 1);
		if (opt == 4) printf("%d\n", T.Kth(x + 1));
		if (opt == 5) printf("%d\n", T.val[T.Next(x, 0)]);
		if (opt == 6) printf("%d\n", T.val[T.Next(x, 1)]);
	}
}