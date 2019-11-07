#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
int n, L, fa[N], fw[N], k, p[N], on[N];
long long x[N], d[N];
std :: pair<long long, int> a[N], b[N];
int edge, to[N << 1], tw[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
std :: pair<long long, int> get_longest(int u){
	std :: pair<long long, int> res = std :: make_pair(0, u), tmp;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u] && !on[v])
			fa[v] = u, fw[v] = tw[i], tmp = get_longest(v), tmp.first += fw[v], res = std :: max(res, tmp);
	return res;
}
long long _A(int p){ return d[p] + x[p]; }
long long _B(int p){ return d[p] - x[p]; }
bool check(long long md){
	long long A = -INF, B = -INF, C = -INF, D = -INF, ma = -INF, mb = -INF;
	for (register int i = 1, j = k; i <= k; ++i){
		for (; j && b[i].first + a[j].first > md; --j)
			ma = std :: max(ma, _A(a[j].second)), mb = std :: max(mb, _B(a[j].second));
		A = std :: max(A, _A(b[i].second) + ma + L - md);
		B = std :: max(B, _B(b[i].second) + ma + L - md);
		C = std :: max(C, _A(b[i].second) + mb + L - md);
		D = std :: max(D, _B(b[i].second) + mb + L - md);
	}
	for (register int i = 1, l1 = k, l2 = 1, r1 = 1, r2 = k; i <= k; ++i){
		while (l1 && x[i] + x[l1 - 1] >= A) --l1;
		while (l2 <= k && -x[i] + x[l2] < B) ++l2;
		while (r1 <= k && x[i] - x[r1 + 1] >= C) ++r1;
		while (r2 && -x[i] - x[r2] < D) --r2;
		if (std :: max(l1, l2) <= std :: min(r1, r2)) return 1;
	}
	return 0;
}
int solve(){
	n = read(), L = read(), edge = 0;
	if (n == 0) return -1;
	for (register int i = 1; i <= n; ++i) hd[i] = 0, on[i] = 0;
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	fa[1] = 0;
	int rt = get_longest(1).second;
	fa[rt] = fw[rt] = 0, k = 0;
	for (register int u = get_longest(rt).second; u; u = fa[u]) p[++k] = u, on[u] = 1;
	for (register int i = 2; i <= k; ++i) x[i] = x[i - 1] + fw[p[i - 1]];
	for (register int i = 1; i <= k; ++i) d[i] = get_longest(p[i]).first;
	for (register int i = 1; i <= k; ++i)
		a[i] = std :: make_pair(_A(i), i), b[i] = std :: make_pair(_B(i), i);
	std :: sort(a + 1, a + 1 + k), std :: sort(b + 1, b + 1 + k);
	long long l = 0, r = 1e15, md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) r = md - 1, ans = md; else l = md + 1;
	printf("%lld\n", ans);
	return 0;
}
int main(){
	while (~solve()) ;
}