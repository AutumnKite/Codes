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
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 100005, P = 998244353, I2 = (P + 1) >> 1;
int n, q, pw[N], pwi[N];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ a < b ? a += P - b : a -= b; }
int plus(int a, int b){ return a + b >= P ? a + b - P : a + b; }
int minus(int a, int b){ return a < b ? a + P - b : a - b; }
struct Segment_Tree{
	int f[N << 2], g[N << 2], sf[N << 2], lz[N << 2];
	void build(int u, int l, int r){
		f[u] = sf[u] = 0, g[u] = 1, lz[u] = 0;
		if (l == r) return;
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
	}
	void mul(int u, int v){
		lz[u] += v, g[u] = 1ll * g[u] * pwi[v] % P;
	}
	void down(int u){
		if (lz[u]) mul(u << 1, lz[u]), mul(u << 1 | 1, lz[u]), lz[u] = 0;
	}
	void work1(int u){
		f[u] = 1ll * f[u] * I2 % P, g[u] = 1ll * (g[u] + 1) * I2 % P;
	}
	void work2(int u){
		dec(sf[u], f[u]), f[u] = 1ll * (f[u] + 1) * I2 % P, inc(sf[u], f[u]);
		g[u] = 1ll * g[u] * I2 % P, ++lz[u];
	}
	void work3(int u){
		dec(sf[u], f[u]), f[u] = 1ll * plus(minus(1, g[u]), f[u]) * I2 % P, inc(sf[u], f[u]);
	}
	void modify(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return work2(u), void(0);
		int md = (l + r) >> 1;
		work1(u), down(u);
		if (L <= md) modify(u << 1, l, md, L, R); else work3(u << 1);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R); else work3(u << 1 | 1);
		sf[u] = plus(sf[u << 1], sf[u << 1 | 1]), inc(sf[u], f[u]);
	}
}T;
int main(){
	n = read(), q = read();
	pw[0] = pwi[0] = 1;
	for (register int i = 1; i <= q; ++i)
		pw[i] = 1ll * pw[i - 1] * 2 % P, pwi[i] = 1ll * pwi[i - 1] * I2 % P;
	T.build(1, 1, n);
	int m = 0;
	while (q--){
		int op = read(), l, r;
		if (op == 2) print(1ll * T.sf[1] * pw[m] % P);
		else l = read(), r = read(), T.modify(1, 1, n, l, r), ++m;
	}
}