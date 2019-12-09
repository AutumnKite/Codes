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
const int P = 998244353;
int n, m, U, E[20], inv[21], f[1 << 20], g[1 << 20], cnt[1 << 20];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
int main(){
	n = read(), m = read(), U = (1 << n) - 1;
	for (register int i = 0; i < n; ++i) E[i] = U ^ (1 << i);
	for (register int i = 1, u, v; i <= m; ++i)
		u = read() - 1, v = read() - 1, E[u] ^= 1 << v, E[v] ^= 1 << u;
	g[0] = 0;
	for (register int S = 1; S < (1 << n); ++S)
		for (register int i = 0; i < n; ++i)
			if (S >> i & 1) g[S] = std :: max(g[S], g[S & E[i]] + 1);
	inv[1] = 1;
	for (register int i = 2; i <= n; ++i) inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
	f[0] = 1, cnt[0] = 0;
	for (register int S = 1; S < (1 << n); ++S){
		for (register int i = 0; i < n; ++i)
			if ((S >> i & 1) && g[S] == g[S & E[i]] + 1)
				inc(f[S], f[S & E[i]]);
		cnt[S] = cnt[S >> 1] + (S & 1);
		f[S] = 1ll * f[S] * inv[cnt[S]] % P;
	}
	printf("%d\n", f[U]);
}