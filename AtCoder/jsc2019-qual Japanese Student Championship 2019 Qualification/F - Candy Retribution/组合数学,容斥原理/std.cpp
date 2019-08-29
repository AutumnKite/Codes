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
#define N 600005
#define P 1000000007
int n, m, l, r, fac[N], inv[N];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n]);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int C(int n, int m){
	if (n < m) return 0;
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
int get(int S, int r){
	if (S < 0) return 0;
	int res = 0;
	for (register int i = 0, t = 0; i <= n - m && t <= S; t += r, ++i){
		int s = 1ll * C(n - m, i) * C(S - t + n, n) % P;
		if (i & 1) dec(res, s); else inc(res, s);
	}
	return 1ll * res * C(n, m) % P;
}
int solve(int S){
	int res = C(S + n, n);
	for (register int i = 1; i * m <= S; ++i)
		dec(res, minus(get(S - i * m, i), get(S - (i + 1) * m, i)));
	return res;
}
int main(){
	n = read(), m = read(), l = read(), r = read();
	init(n + r);
	printf("%d\n", minus(solve(r), solve(l - 1)));
}
