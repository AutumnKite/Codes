#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int T, n, m, a[5][105];
struct node{
	int x, y, w;
	bool operator < (const node &rhs) const {
		return w > rhs.w;
	}
}b[1005];
bool check(node a, node b, node c, node d){
	std :: pair<int, int> p[4];
	p[0] = std :: make_pair(a.y, a.x);
	p[1] = std :: make_pair(b.y, b.x);
	p[2] = std :: make_pair(c.y, c.x);
	p[3] = std :: make_pair(d.y, d.x);
	std :: sort(p, p + 4);
	if (p[0].first == p[1].first && p[1].first < p[2].first && p[2].first == p[3].first){
		if (p[1].second - p[0].second != 2 && p[3].second - p[2].second == 2) return 0;
		if (p[1].second - p[0].second == 2 && p[3].second - p[2].second != 2) return 0;
	}
	return 1;
}
void solve(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			a[i][j] = read(), b[(i - 1) * m + j] = (node){i, j, a[i][j]};
	std :: sort(b + 1, b + 1 + n * m);
	if (n <= 3 || check(b[1], b[2], b[3], b[4])){
		long long ans = 0;
		for (register int i = 1; i <= n; ++i) ans += b[i].w;
		return printf("%lld\n", ans), void(0);
	}
	long long ans = b[1].w + b[2].w;
	if (check(b[1], b[2], b[3], b[5])) printf("%lld\n", ans + b[3].w + b[5].w), void(0);
	printf("%lld\n", ans + std :: max(b[3].w + b[6].w, b[4].w + b[5].w)), void(0);
}
int main(){
	T = read();
	while (T--) solve();
}