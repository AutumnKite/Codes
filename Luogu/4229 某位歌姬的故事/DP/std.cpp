#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int P = 998244353;
int n, q, lim, m, b[1005], w[1005], k, pos[1005], l[1005], dp[1005], ans;
struct node{
	int l, r, x;
	bool operator < (const node &rhs) const {
		return x < rhs.x;
	}
}a[505];
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int work(int x){
	k = 0;
	for (register int i = 1; i < m; ++i)
		if (w[i] == x) pos[++k] = i, l[k] = 0;
	l[k + 1] = 0;
	for (register int i = 1; i <= q; ++i)
		if (a[i].x == x){
			int L = std :: lower_bound(pos + 1, pos + 1 + k, a[i].l) - pos;
			int R = std :: lower_bound(pos + 1, pos + 1 + k, a[i].r) - pos;
			if (L == R) return 0;
			l[R] = std :: max(l[R], L);
		}
	for (register int i = 1; i <= k + 1; ++i) l[i] = std :: max(l[i - 1], l[i]);
	dp[0] = 1;
	for (register int i = 1; i <= k + 1; ++i){
		int v;
		if (i <= k) v = minus(qpow(x, b[pos[i] + 1] - b[pos[i]]), qpow(x - 1, b[pos[i] + 1] - b[pos[i]]));
		else v = 1;
		dp[i] = 0;
		for (register int j = i - 1; j >= l[i]; --j){
			inc(dp[i], 1ll * dp[j] * v % P);
			if (j) v = 1ll * v * qpow(x - 1, b[pos[j] + 1] - b[pos[j]]) % P;
		}
		// printf("%d %d\n", v, dp[i]);
	}
	// putchar('\n');
	return dp[k + 1];
}
void solve(){
	n = read(), q = read(), lim = read(), m = 0;
	b[++m] = 1, b[++m] = n + 1;
	for (register int i = 1; i <= q; ++i)
		a[i].l = b[++m] = read(), a[i].r = b[++m] = read() + 1, a[i].x = read();
	std :: sort(b + 1, b + 1 + m);
	m = std :: unique(b + 1, b + 1 + m) - b - 1;
	for (register int i = 1; i < m; ++i) w[i] = lim + 1;
	for (register int i = 1; i <= q; ++i){
		a[i].l = std :: lower_bound(b + 1, b + 1 + m, a[i].l) - b;
		a[i].r = std :: lower_bound(b + 1, b + 1 + m, a[i].r) - b;
		for (register int j = a[i].l; j < a[i].r; ++j) w[j] = std :: min(w[j], a[i].x);
	}
	std :: sort(a + 1, a + 1 + q);
	ans = work(a[1].x);
	for (register int i = 2; i <= q; ++i)
		if (a[i].x > a[i - 1].x) ans = 1ll * ans * work(a[i].x) % P;
	for (register int i = 1; i < m; ++i)
		if (w[i] == lim + 1) ans = 1ll * ans * qpow(lim, b[i + 1] - b[i]) % P;
	printf("%d\n", ans);
}
int main(){
	int T = read();
	while (T--) solve();
}
