#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, w[205], v[205];
long long sw, sv;
namespace Subtask1{
	int na, cnta, nb;
	long long ans;
	struct node{
		long long W, V;
		bool operator < (const node &rhs) const {
			return W < rhs.W || (W == rhs.W && V > rhs.V);
		}
	}a[50005];
	void Main(){
		na = n >> 1, nb = n - na;
		for (register int p = 0; p < (1 << na); ++p){
			++cnta;
			a[cnta].W = a[cnta].V = 0;
			for (register int i = 0; i < na; ++i)
				if (p >> i & 1) a[cnta].W += w[i + 1], a[cnta].V += v[i + 1];
			if (a[cnta].W > m) --cnta;
		}
		std :: sort(a + 1, a + 1 + cnta);
		for (register int i = 2; i <= cnta; ++i)
			a[i].V = std :: max(a[i].V, a[i - 1].V);
		for (register int p = 0; p < (1 << nb); ++p){
			node cur;
			cur.W = 0, cur.V = 0;
			for (register int i = 0; i < nb; ++i)
				if (p >> i & 1) cur.W += w[na + i + 1], cur.V += v[na + i + 1];
			if (cur.W > m) continue;
			cur.W = m - cur.W + 1;
			int t = std :: lower_bound(a + 1, a + 1 + cnta, cur) - a - 1;
			ans = std :: max(ans, cur.V + a[t].V);
		}
		printf("%lld\n", ans);
	}
}
namespace Subtask2{
	long long dp[200005];
	void Main(){
		if (m < sw) sw = m;
		for (register int i = 1; i <= n; ++i)
			for (register int j = sw; j >= w[i]; --j)
				dp[j] = std :: max(dp[j], dp[j - w[i]] + v[i]);
		printf("%lld\n", dp[sw]);
	}
}
namespace Subtask3{
	long long dp[200005];
	void Main(){
		memset(dp, 0x3f, sizeof dp);
		dp[0] = 0;
		for (register int i = 1; i <= n; ++i)
			for (register int j = sv; j >= v[i]; --j)
				dp[j] = std :: min(dp[j], dp[j - v[i]] + w[i]);
		for (register int j = sv; ~j; --j)
			if (dp[j] <= m) return printf("%d\n", j), void(0);
	}
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		sv += v[i] = read(), sw += w[i] = read();
	if (n <= 30) return Subtask1 :: Main(), 0;
	if (sw <= 200000) return Subtask2 :: Main(), 0;
	if (sv <= 200000) return Subtask3 :: Main(), 0;
}
