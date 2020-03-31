#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N = 200005, P = 1000000007;
int n;
std::vector<int> E[N];
int fac[N], inv[N];
int sz[N], f[N], g[N], ans[N];
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n], P - 2);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int C(int n, int m){
	if (m < 0 || m > n) return 0;
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P; 
}
void dfs_f(int u, int fa = 0){
	f[u] = 1, sz[u] = 1;
	for (int v : E[u])
		if (v != fa){
			dfs_f(v, u), sz[u] += sz[v];
			f[u] = 1ll * f[u] * f[v] % P * C(sz[u] - 1, sz[v]) % P;
		}
}
void dfs_g(int u, int fa = 0){
	ans[u] = 1ll * f[u] * g[u] % P * C(n - 1, n - sz[u]) % P;
	for (int v : E[u])
		if (v != fa){
			g[v] = 1ll * ans[u] * qpow(1ll * f[v] * C(n - 1, sz[v]) % P, P - 2) % P;
			dfs_g(v, u);
		}
}
int main(){
	scanf("%d", &n);
	for (register int i = 1, u, v; i < n; ++i)
		scanf("%d%d", &u, &v), E[u].push_back(v), E[v].push_back(u);
	init(n);
	dfs_f(1), g[1] = 1, dfs_g(1);
	for (register int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
}
