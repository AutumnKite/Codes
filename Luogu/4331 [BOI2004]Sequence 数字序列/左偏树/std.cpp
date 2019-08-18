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
#define N 1000005
int n, a[N];
namespace Leftist_Tree_Forest{
	int cnt, rt[N], sz[N], fa[N], ls[N], rs[N], dep[N], val[N], siz[N];
	int merge(int x, int y){
		if (!x || !y) return x + y;
		if (val[x] > val[y]) std :: swap(x, y);
		rs[x] = merge(rs[x], y), fa[rs[x]] = x;
		if (dep[ls[x]] < dep[rs[x]]) std :: swap(ls[x], rs[x]);
		siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
		return dep[x] = dep[ls[x]] + 1, x;
	}
	int Delete(int u){
		int x = rt[u];
		int ans = val[x];
		val[x] = -1, fa[ls[x]] = fa[rs[x]] = 0, dep[x] = 0, siz[x] = 0;
		rt[u] = merge(ls[x], rs[x]), fa[x] = ls[x] = rs[x] = 0;
		return ans;
	}
}
using namespace Leftist_Tree_Forest;
long long abs(long long a){
	return a > 0 ? a : -a;
}
long long ans;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read() - i;
	for (register int i = 1; i <= n; ++i){
		rt[++cnt] = i, sz[cnt] = 1, 
		fa[i] = ls[i] = rs[i] = dep[i] = 0, val[i] = a[i], siz[i] = 1;
		while (cnt > 1 && val[rt[cnt]] < val[rt[cnt - 1]]){
			--cnt;
			rt[cnt] = merge(rt[cnt], rt[cnt + 1]);
			sz[cnt] += sz[cnt + 1];
			if (siz[rt[cnt]] > siz[rt[cnt]] - (sz[cnt] >> 1)) Delete(cnt);
		}
	}
	int m = 0;
	for (register int i = 1; i <= cnt; ++i)
		for (register int j = 1; j <= sz[i]; ++j)
			++m, ans += abs(a[m] - val[rt[i]]), a[m] = val[rt[i]];
	printf("%lld\n", ans);
	for (register int i = 1; i <= n; ++i) printf("%d ", a[i] + i);
}