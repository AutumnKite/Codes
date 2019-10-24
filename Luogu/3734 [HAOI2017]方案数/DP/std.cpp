#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 10005
#define P 998244353
int bitcnt(long long x){
	int res = 0;
	while (x) x &= x - 1, ++res;
	return res;
}
struct node{
	long long x, y, z;
	int bx, by, bz;
	void init(){
		x = read(), y = read(), z = read();
		bx = bitcnt(x), by = bitcnt(y), bz = bitcnt(z);
	}
	bool operator < (const node &rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y) || (x == rhs.x && y == rhs.y && z < rhs.z);
	}
	bool in(node &rhs){
		return (x & rhs.x) == x && (y & rhs.y) == y && (z & rhs.z) == z;
	}
}a[N], ed;
int n, m, C[61][61], dp[61][61][61], f[N];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
int add(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int main(){
	ed.init(), n = read(), m = 0;
	for (register int i = 1; i <= n; ++i){
		node tmp;
		tmp.init();
		if (tmp.in(ed)) a[++m] = tmp;
	}
	std :: sort(a + 1, a + 1 + m);
	a[++m] = ed;
	for (register int i = 0; i <= 60; ++i){
		C[i][0] = C[i][i] = 1;
		for (register int j = 1; j < i; ++j)
			C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
	}
	dp[0][0][0] = 1;
	for (register int i = 0; i <= ed.bx; ++i)
		for (register int j = 0; j <= ed.by; ++j)
			for (register int k = 0; k <= ed.bz; ++k)
				if (i || j || k){
					dp[i][j][k] = 0;
					for (register int x = 0; x < i; ++x)
						inc(dp[i][j][k], 1ll * dp[x][j][k] * C[i][x] % P);
					for (register int x = 0; x < j; ++x)
						inc(dp[i][j][k], 1ll * dp[i][x][k] * C[j][x] % P);
					for (register int x = 0; x < k; ++x)
						inc(dp[i][j][k], 1ll * dp[i][j][x] * C[k][x] % P);
				}
	for (register int i = 1; i <= m; ++i){
		f[i] = dp[a[i].bx][a[i].by][a[i].bz];
		for (register int j = 1; j < i; ++j)
			if (a[j].in(a[i]))
				dec(f[i], 1ll * f[j] * dp[a[i].bx - a[j].bx][a[i].by - a[j].by][a[i].bz - a[j].bz] % P);
	}
	printf("%d\n", f[m]);
}
