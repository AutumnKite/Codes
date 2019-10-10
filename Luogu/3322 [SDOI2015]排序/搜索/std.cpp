#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
int n, a[1 << 12];
long long ans, fac[15];
void Swap(int k, int p0, int p1 = -1){
	if (p1 == -1) p1 = p0 + (1 << k);
	for (register int i = 0; i < (1 << k); ++i)
		std :: swap(a[p0 + i], a[p1 + i]);
}
void dfs(int k, int s){
	if (k == n) return ans += fac[s], void(0);
	int cnt = 0, pos[2];
	for (register int i = 0; i < (1 << n); i += 1 << (k + 1))
		if (a[i] + (1 << k) != a[i + (1 << k)])
			if (cnt >= 2) return; else pos[cnt] = i, ++cnt;
	if (cnt == 0) return dfs(k + 1, s), void(0);
	if (cnt == 1) return Swap(k, pos[0]), dfs(k + 1, s + 1), Swap(k, pos[0]), void(0);
	int x0 = pos[0], x1 = x0 + (1 << k), y0 = pos[1], y1 = y0 + (1 << k);
	if (a[x0] + (1 << k) == a[y0] && a[x1] + (1 << k) == a[y1]) Swap(k, x1, y0), dfs(k + 1, s + 1), Swap(k, x1, y0);
	if (a[x0] + (1 << k) == a[y1] && a[y0] + (1 << k) == a[x1]) Swap(k, x1, y1), dfs(k + 1, s + 1), Swap(k, x1, y1);
	if (a[y0] + (1 << k) == a[x1] && a[x0] + (1 << k) == a[y1]) Swap(k, x0, y0), dfs(k + 1, s + 1), Swap(k, x0, y0);
	if (a[y1] + (1 << k) == a[x1] && a[y0] + (1 << k) == a[x0]) Swap(k, x0, y1), dfs(k + 1, s + 1), Swap(k, x0, y1);
}
int main(){
	n = read();
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
	for (register int i = 0; i < (1 << n); ++i) a[i] = read() - 1;
	dfs(0, 0);
	printf("%lld\n", ans);
}
