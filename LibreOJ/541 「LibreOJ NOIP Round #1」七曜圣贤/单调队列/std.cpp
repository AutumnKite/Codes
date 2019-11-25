#include <cstdio>
unsigned int seed;
inline unsigned int rnd(){
	return seed ^= seed << 13, seed ^= seed >> 17, seed ^= seed << 5;
}
const int N = 1000005;
int n, a, b, c, d, vis[N << 1], mex, h, t, l, r, id[N], Q[N], ans_sum;
void solve(){
	scanf("%d%u%d%d%d%d", &n, &seed, &a, &b, &c, &d), mex = a + 1;
	for (register int i = 0; i <= b; ++i) vis[i] = 0;
	for (register int i = 0; i <= a; ++i) vis[i] = 1;
	h = 1, t = 0, l = 1, r = 0, ans_sum = 0;
	for (register int i = 1; i <= n; ++i){
		register int p = rnd() % c == 0 ? -1 : rnd() % b, ans = 0;
		if (~p && !vis[p]){
			vis[p] = 1;
			while (vis[mex]) ++mex;
			if (h <= t && id[Q[h]] < mex) ans = id[Q[h]]; else ans = mex;
		}
		else if (!d && ~p && vis[p] == 1){
			vis[p] = 2;
			while (h <= t && p < id[Q[t]]) --t;
			id[++r] = p, Q[++t] = r;
			if (h <= t && id[Q[h]] < mex) ans = id[Q[h]]; else ans = mex;
		}
		else if (!d && (p == -1 || vis[p] == 2) && l <= r){
			if (Q[h] == l) ++h;
			vis[id[l]] = 1, ++l;
			if (h <= t && id[Q[h]] < mex) ans = id[Q[h]]; else ans = mex;
		}
		ans_sum ^= 1ll * i * (i + 7) % 998244353 * ans % 998244353;
	}
	printf("%d\n", ans_sum);
}
int main(){
	int T;
	scanf("%d", &T);
	while (T--) solve();
}