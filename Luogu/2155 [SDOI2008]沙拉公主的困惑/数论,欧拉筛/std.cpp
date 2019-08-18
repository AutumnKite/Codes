#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1000005
int T, P, n_[10005], m_[10005], M, cnt, p[N], Inv[N * 10], ans[N], fac[N * 10];
bool vis[N * 10];
void init(int n){
	vis[1] = 1;
	for (register int i = 2; i <= n; ++i){
		if (!vis[i]) p[++cnt] = i;
		for (register int j = 1; j <= cnt && i * p[j] <= n; ++j){
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
	Inv[0] = Inv[1] = 1;
	for (register int i = 2, i_E = std :: min(n - 1, P); i <= i_E; ++i)
		Inv[i] = 1ll * (P - P / i) * Inv[P % i] % P;
	for (register int i = P; i <= n; ++i) Inv[i] = Inv[i % P];
	ans[0] = 1;
	for (register int i = 1; i <= cnt; ++i)
		ans[i] = 1ll * ans[i - 1] * (p[i] - 1) % P * Inv[p[i]] % P;
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i)
		if (i % P) fac[i] = 1ll * fac[i - 1] * i % P; else fac[i] = fac[i - 1];
}
int main(){
	scanf("%d%d", &T, &P);
	for (register int i = 1; i <= T; ++i)
		scanf("%d%d", n_ + i, m_ + i), M = std :: max(M, n_[i]);
	init(M);
	for (register int i = 1; i <= T; ++i){
		int n = n_[i], m = m_[i];
		if (n >= P && m < P){ printf("0\n"); continue; }
		m = std :: upper_bound(p + 1, p + 1 + cnt, m) - p - 1;
		printf("%d\n", 1ll * fac[n] * ans[m] % P);
	}
}
