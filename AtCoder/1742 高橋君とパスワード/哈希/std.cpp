#include <cstdio>
#include <cstring>
#include <algorithm>
char a[305];
#define P1 998244353
#define P2 1000000007
int n, m, s1[305], s2[305], w1[305], w2[305];
std :: pair<int, int> sub[305];
int main(){
	scanf("%s", a + 1), n = strlen(a + 1), w1[0] = w2[0] = 1, scanf("%d", &m);
	if (m > n) return printf("0\n"), 0;
	for (register int i = 1; i <= n; ++i)
		w1[i] = 1ll * w1[i - 1] * 29 % P1, w2[i] = 1ll * w2[i - 1] * 31 % P2;
	for (register int i = 1; i <= n; ++i)
		s1[i] = (1ll * s1[i - 1] * 29 + a[i] - 'a') % P1, s2[i] = (1ll * s2[i - 1] * 31 + a[i] - 'a') % P2;
	for (register int i = m; i <= n; ++i)
		sub[i - m + 1].first = (s1[i] - 1ll * s1[i - m] * w1[m] % P1 + P1) % P1,
		sub[i - m + 1].second = (s2[i] - 1ll * s2[i - m] * w2[m] % P2 + P2) % P2;
	std :: sort(sub + 1, sub + n - m + 1 + 1);
	int ans = std :: unique(sub + 1, sub + n - m + 1 + 1) - sub - 1;
	printf("%d\n", ans);
}