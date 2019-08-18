#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 5005
#define M 10000005
int n, m, a[N], cnt[M], cntt[M];
long long ans;
long long C2(long long x){ return x < 2 ? 0 : x * (x - 1) / 2; }
long long C3(long long x){ return x < 3 ? 0 : x * (x - 1) * (x - 2) / 6; }
long long C4(long long x){ return x < 4 ? 0 : x * (x - 1) * (x - 2) * (x - 3) / 24; }
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), ++cnt[a[i]];
	std :: sort(a + 1, a + 1 + n);
	m = a[n];
	n = std :: unique(a + 1, a + 1 + n) - a - 1;
	for (register int i = 1; i <= n; ++i){
		for (register int j = i + 1; j <= n && a[j] - a[i] < a[i]; ++j)
			ans += 1ll * cntt[a[j]] * cnt[a[i]] * cnt[a[j] - a[i]] * C2(cnt[a[j]]),
			ans += 1ll * C2(cnt[a[i]]) * C2(cnt[a[j] - a[i]]) * C2(cnt[a[j]]);
		if (a[i] * 2 <= m) ans += 1ll * C4(cnt[a[i]]) * C2(cnt[a[i] * 2]);
		for (register int j = i + 1; j <= n; ++j){
			ans += 1ll * C3(cnt[a[j]]) * cnt[a[i]] * cntt[a[j] - a[i]];
			if ((a[i] << 1) < a[j] && a[j] < a[i] * 3)
				ans += 1ll * C3(cnt[a[j]]) * C2(cnt[a[i]]) * cnt[a[j] - (a[i] << 1)];
			if (a[j] == a[i] * 3) ans += 1ll * C3(cnt[a[j]]) * C3(cnt[a[i]]);
		}
		for (register int j = 1; j < i; ++j)
			if (a[i] + a[j] <= m) cntt[a[i] + a[j]] += cnt[a[i]] * cnt[a[j]];
		if ((a[i] << 1) <= m) cntt[a[i] << 1] += C2(cnt[a[i]]);
	}
	printf("%lld\n", ans);
}
