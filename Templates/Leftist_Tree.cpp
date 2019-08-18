#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register int ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, m;
struct Leftist_Tree_Forest{
	int fa[N], ls[N], rs[N], dep[N], val[N];
	int merge(int x, int y){
		if (!x || !y) return x + y;
		if (val[x] > val[y]) std :: swap(x, y);
		rs[x] = merge(rs[x], y), fa[rs[x]] = x;
		if (dep[ls[x]] < dep[rs[x]]) std :: swap(ls[x], rs[x]);
		return dep[x] = dep[ls[x]] + 1, x;
	}
	int find(int x){
		return !fa[x] ? x : find(fa[x]);
	}
	void Merge(int x, int y){
		if (val[x] == -1 || val[y] == -1) return;
		int fx = find(x), fy = find(y);
		if (fx == fy) return;
		merge(fx, fy);
	}
	int Delete(int x){
		if (val[x] == -1) return -1;
		x = find(x);
		int ans = val[x];
		val[x] = -1, fa[ls[x]] = fa[rs[x]] = 0, dep[x] = 0, 
		merge(ls[x], rs[x]), fa[x] = ls[x] = rs[x] = 0;
		return ans;
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		T.val[i] = read(), T.fa[i] = T.ls[i] = T.rs[i] = 0;
	while (m--){
		int opt = read(), x = read();
		if (opt == 1) T.Merge(x, read());
		else printf("%d\n", T.Delete(x));
	}
}