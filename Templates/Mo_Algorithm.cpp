#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 50005
int n, m, blo, s[N], c[N], l, r;
long long ansx[N], ansy[N], now;
struct query{
	int l, r, id, bl;
	bool operator < (const query &b) const {
		return bl < b.bl || bl == b.bl && r < b.r;
	}
}q[N];
void update(int p, int add){
	now -= 1ll * s[c[p]] * (s[c[p]] - 1), s[c[p]] += add, now += 1ll * s[c[p]] * (s[c[p]] - 1);
}
long long gcd(long long a, long long b){
	return b ? gcd(b, a % b) : a;
}
int main(){
	scanf("%d%d", &n, &m), blo = sqrt(n);
	for (register int i = 1; i <= n; ++i) scanf("%d", c + i);
	for (register int i = 1; i <= m; ++i)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i, q[i].bl = (q[i].l - 1) / blo + 1;
	std :: sort(q + 1, q + 1 + m);
	l = 1, r = 0;
	for (register int i = 1; i <= m; ++i){
		while (l < q[i].l) update(l++, -1);
		while (l > q[i].l) update(--l, 1);
		while (r < q[i].r) update(++r, 1);
		while (r > q[i].r) update(r--, -1);
		if (l == r) ansx[q[i].id] = 0, ansy[q[i].id] = 1;
		else ansx[q[i].id] = now, ansy[q[i].id] = 1ll * (r - l + 1) * (r - l);
	}
	for (register int i = 1; i <= m; ++i){
		long long g = gcd(ansx[i], ansy[i]);
		printf("%lld/%lld\n", ansx[i] / g, ansy[i] / g);
	}
}