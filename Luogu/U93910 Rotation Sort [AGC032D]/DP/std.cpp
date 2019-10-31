#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 5005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, a[N];
long long A, B, dp[N];
int main(){
	n = read(), A = read(), B = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	dp[0] = 0, a[0] = 0, a[n + 1] = n + 1;
	for (register int i = 1; i <= n + 1; ++i){
		dp[i] = INF;
		for (register int j = i - 1, s = 0; ~j; --j)
			if (a[j] < a[i]) dp[i] = std :: min(dp[i], dp[j] + B * s + A * (i - j - 1 - s)), ++s;
	}
	printf("%lld\n", dp[n + 1]);
}