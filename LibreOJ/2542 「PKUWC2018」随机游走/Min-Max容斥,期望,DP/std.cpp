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
int n, q, rt, E[18], cnt[1 << 18], Log[1 << 18 | 1], A[18], B[18], f[1 << 18];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
int plus(int a, int b){ return a + b >= P ? a + b - P : a + b; }
int minus(int a, int b){ return a < b ? a + P - b : a - b; }
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void dfs(int S, int u, int fa = -1){
	if (S >> u & 1) return A[u] = B[u] = 0, void(0);
	int sa = 0, sb = 0, d = cnt[E[u]];
	for (register int i = E[u], v; i; i &= i - 1)
		if ((v = Log[i & -i]) != fa)
			dfs(S, v, u), inc(sa, A[v]), inc(sb, B[v]);
	A[u] = qpow(minus(d, sa), P - 2), B[u] = 1ll * A[u] * (sb + d) % P;
}
int main(){
	n = read(), q = read(), rt = read() - 1;
	for (register int i = 1, u, v; i < n; ++i)
		u = read() - 1, v = read() - 1, E[u] |= 1 << v, E[v] |= 1 << u;
	Log[1] = 0;
	for (register int i = 2; i <= (1 << n); ++i) Log[i] = Log[i >> 1] + 1;
	cnt[0] = 0;
	for (register int S = 1; S < (1 << n); ++S) cnt[S] = cnt[S >> 1] + (S & 1);
	for (register int S = 1; S < (1 << n); ++S)
		dfs(S, rt), f[S] = cnt[S] & 1 ? B[rt] : P - B[rt];
	for (register int i = 0; i < n; ++i)
		for (register int S = 0; S < (1 << n); ++S)
			if (S >> i & 1) inc(f[S], f[S ^ (1 << i)]);
	while (q--){
		int k = read(), st = 0;
		for (register int i = 0, u; i < k; ++i) u = read() - 1, st |= 1 << u;
		printf("%d\n", f[st]);
	}
}