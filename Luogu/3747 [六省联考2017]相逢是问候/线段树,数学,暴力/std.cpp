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
void print(int x){
	int cnt = 0, num[30];
	if (x == 0) return putchar('0'), void(0);
	while (x) num[++cnt] = x % 10, x /= 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
}
#define N 50005
#define M 10000000
#define INF 0x3f3f3f3f
int n, q, _p, p[75], c, need, a[N], b[N][7];
int pw[75][1 << 15], Pw[75][1 << 15];
int get_phi(int x){
	int s = x;
	for (register int i = 2; i * i <= x; ++i)
		if (x % i == 0){
			s = 1ll * s * (i - 1) / i;
			while (x % i == 0) x /= i;
		}
	if (x > 1) s = 1ll * s * (x - 1) / x;
	return s;
}
int qpow(int b, int pid){
	return 1ll * Pw[pid][b >> 15] * pw[pid][b & 32767] % p[pid];
}
int calc(int md, int d, int x){
	if (p[d] == 1) return 0;
	if (d == md) return a[x] % p[d];
	if (md - d + 1 <= 6 && b[x][md - d - 1] < p[d + 1])
		return qpow(b[x][md - d - 1], d);
	return qpow(calc(md, d + 1, x) + p[d + 1], d);
}
namespace SegT{
	int mn[N << 2];
	long long sum[N << 2];
	void build(int u, int l, int r){
		if (l == r) return sum[u] = a[l], void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
	}
	void modify(int u, int l, int r, int L, int R){
		if (l == r) return ++mn[u], sum[u] = calc(mn[u], 0, l), void(0);
		int md = (l + r) >> 1;
		if (L <= md && mn[u << 1] < need) modify(u << 1, l, md, L, R);
		if (R > md && mn[u << 1 | 1] < need) modify(u << 1 | 1, md + 1, r, L, R);
		mn[u] = std :: min(mn[u << 1], mn[u << 1 | 1]);
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
	}
	long long query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return sum[u];
		int md = (l + r) >> 1;
		if (R <= md) return query(u << 1, l, md, L, R);
		else if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		else return query(u << 1, l, md, L, R) + query(u << 1 | 1, md + 1, r, L, R);
	}
}
int main(){
	n = read(), q = read(), _p = read(), c = read();
	while (_p > 1) p[need++] = _p, _p = get_phi(_p);
	for (register int i = 0; i < need; ++i){
		pw[i][0] = 1;
		for (register int j = 1; j < (1 << 15); ++j) pw[i][j] = 1ll * pw[i][j - 1] * c % p[i];
		int cp = 1ll * pw[i][32767] * c % p[i];
		Pw[i][0] = 1;
		for (register int j = 1; j < (1 << 15); ++j) Pw[i][j] = 1ll * Pw[i][j - 1] * cp % p[i];
	}
	for (register int i = 1; i <= 6; ++i) p[need++] = 1;
	p[need] = 1;
	for (register int i = 1; i <= n; ++i){
		a[i] = read(), b[i][0] = a[i];
		for (register int j = 1; j <= 6; ++j){
			if (b[i][j - 1] == INF){ b[i][j] = INF; continue; }
			b[i][j] = 1;
			for (register int k = 1; k <= b[i][j - 1]; ++k)
				if (b[i][j] <= INF / c) b[i][j] = b[i][j] * c;
				else { b[i][j] = INF; break; }
		}
	}
	SegT :: build(1, 1, n);
	while (q--){
		int op = read(), l = read(), r = read();
		if (op) print(SegT :: query(1, 1, n, l, r) % p[0]), putchar('\n');
		else SegT :: modify(1, 1, n, l, r);
	}
}