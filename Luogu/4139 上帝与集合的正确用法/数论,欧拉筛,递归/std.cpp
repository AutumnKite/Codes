#include <cstdio>
#include <algorithm>
int T, n, q[10005], cnt, p[10000005], phi[10000005];
bool vis[10000005];
void init(int n){
	vis[1] = 1, phi[1] = 1;
	for (register int i = 2; i <= n; ++i){
		if (!vis[i]) p[++cnt] = i, phi[i] = i - 1;
		for (register int j = 1; j <= cnt && i * p[j] <= n; ++j){
			vis[i * p[j]] = 1;
			if (i % p[j] == 0){ phi[i * p[j]] = phi[i] * p[j]; break; }
			else phi[i * p[j]] = phi[i] * phi[p[j]];
		}
	}
}
int qpow(int a, int b, int P){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int query(int P){
	if (P == 1) return 0;
	else return qpow(2, query(phi[P]) + phi[P], P);
}
int main(){
	scanf("%d", &T);
	for (register int i = 1; i <= T; ++i)
		scanf("%d", q + i), n = std :: max(n, q[i]);
	init(n);
	for (register int i = 1; i <= T; ++i) printf("%d\n", query(q[i]));
}