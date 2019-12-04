#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 200005;
int n, m, q, a[N];
long long ans[N];
std :: vector<int> pos[N];
std :: vector< std :: pair<std :: pair<int, int>, int> > Q[N];
std :: vector< std :: pair<int, int> > f, g;
std :: vector<long long> sum;
int find(int x){
	return std :: lower_bound(f.begin(), f.end(), std :: make_pair(x, 0)) - f.begin();
}
bool cmp(std :: pair<int, int> a, std :: pair<int, int> b){
	return a.second < b.second;
}
int find_v(int x){
	return std :: lower_bound(f.begin(), f.end(), std :: make_pair(0, x), cmp) - f.begin();
}
int main(){
	n = read(), m = read(), q = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
	for (register int i = 1, l, r, k; i <= q; ++i)
		l = read(), r = read(), k = read(), Q[k].push_back({{l, r}, i});
	f.push_back({n + 2, n + 2});
	for (register int k = 1; k <= m; ++k){
		int p = 0;
		g.clear();
		for (int v : pos[k]){
			int tmp;
			while (p < f.size() && (tmp = f[find(f[p].second)].second) <= v)
				g.push_back({f[p].first, tmp}), ++p;
			if (g.empty() || g.back().first <= v) g.push_back({v, v + 1});
			while (p < f.size() && f[p].first <= v) ++p;
		}
		while (p < f.size())
			g.push_back({f[p].first, f[find(f[p].second)].second}), ++p;
		f.clear();
		for (register int i = 0; i < g.size(); ++i)
			if (f.empty() || f.back().second != g[i].second) f.push_back(g[i]);
			else f.back().first = g[i].first;
		sum.clear(), sum.push_back(0), p = 0;
		for (auto v : f) sum.push_back(1ll * (v.first - p) * v.second), p = v.first;
		sum.pop_back();
		for (register int i = 1; i < sum.size(); ++i) sum[i] += sum[i - 1];
		for (auto v : Q[k]){
			int l = v.first.first - 1, r = v.first.second + 1, id = v.second;
			int pr = find_v(r + 1), pl = find(l);
			int lst = pl ? f[pl - 1].first : 0, md = pr ? f[pr - 1].first : 0;
			long long tmp = 1ll * f[pl].second * (l - lst);
			if (l > md) continue;
			ans[id] = 1ll * (md - l) * (r + 1) - std :: max(0ll, sum[pr] - sum[pl] - tmp);
		}
	}
	for (register int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
}