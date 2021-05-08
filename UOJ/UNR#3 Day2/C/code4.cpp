#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const int N = 1e5 + 10;
int n, m, a[N], q[N], head, tail;
ll dp[N];
pli Q[N];
int Head, Tail;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	Head = 1;
	Tail = 0;
	head = tail = 1;
	for (int i = 1; i <= n; i++) {
		for (; head <= tail && a[q[tail]] <= a[i]; tail--)
			if (Head <= Tail && Q[Tail].second == q[tail - 1]) Tail--;
		q[++tail] = i;
		if (head < tail) {
			ll v = dp[q[tail - 1]] + a[i];
			for (; Head <= Tail && Q[Tail].first >= v; Tail--)
				;
			Q[++Tail] = pli(v, q[tail - 1]);
		}
		for (; i - q[head] > m; head++)
			if (Head <= Tail && Q[Head].second == q[head]) Head++;
		dp[i] = min(dp[max(i - m, 0)] + a[q[head]],
								Head <= Tail ? Q[Head].first : (ll)1e18);
	}
	printf("%lld\n", dp[n]);
	return 0;
}
