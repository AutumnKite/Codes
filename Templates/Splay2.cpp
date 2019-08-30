#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	int x = 0, f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
struct Splay{
	int cnt, rt, fa[N], son[N][2], sz[N], val[N], rev[N], len, ans[N];
	int new_node(int x){
		return val[++cnt] = x, son[cnt][0] = son[cnt][1] = 0, sz[cnt] = 1, rev[cnt] = 0, cnt;
	}
	void update(int x){
		sz[x] = sz[son[x][0]] + sz[son[x][1]] + 1;
	}
	void down(int x){
		if (rev[x]){
			if (son[x][0]) rev[son[x][0]] ^= 1;
			if (son[x][1]) rev[son[x][1]] ^= 1;
			rev[x] = 0, std :: swap(son[x][0], son[x][1]);
		}
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
	void build(int &u, int f, int l, int r){
		if (l > r) return void(u = 0);
		int mid = (l + r) >> 1;
		u = new_node(mid), fa[u] = f;
		build(son[u][0], u, l, mid - 1), build(son[u][1], u, mid + 1, r), update(u);
	}
	int kth(int x){
		int u = rt;
		while (2333){
			down(u);
			if (x > sz[son[u][0]] + 1) x -= sz[son[u][0]] + 1, u = son[u][1];
			else if (x <= sz[son[u][0]]) u = son[u][0];
			else return u;
		}
	}
	void reverse(int l, int r){
		splay(kth(l), 0), splay(kth(r + 2), rt), rev[son[son[rt][1]][0]] ^= 1;
	}
	void get_ans(int u){
		if (!u) return;
		down(u), get_ans(son[u][0]), ans[++len] = val[u], get_ans(son[u][1]);
	}
}T;
int n, m;
int main(){
	n = read(), m = read(), T.build(T.rt, 0, 1, n + 2);
	while (m--){
		int l = read(), r = read();
		T.reverse(l, r);
	}
	T.get_ans(T.rt);
	for (register int i = 2; i <= n + 1; ++i) printf("%d ", T.ans[i] - 1);
}