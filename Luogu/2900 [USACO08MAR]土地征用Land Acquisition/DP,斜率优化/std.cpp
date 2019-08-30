#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 50005
int n, s[N], t, h;
long long dp[N];
struct node{
	int r, c;
	bool operator < (const node &res) const {
		return r < res.r || r == res.r && c < res.c;
	}
}a[N], b[N];
long long X(int i, int j){
	return dp[i] - dp[j];
}
long long Y(int i, int j){
	return a[i + 1].c - a[j + 1].c;
}
long long val(int i, int j){
	return dp[j] + 1ll * a[i].r * a[j + 1].c;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d%d", &b[i].r, &b[i].c);
	std :: sort(b + 1, b + 1 + n);
	for (register int i = 1; i <= n; ++i){
		while (t && b[i].c >= b[s[t]].c) --t;
		s[++t] = i;
	}
	n = t;
	for (register int i = 1; i <= n; ++i) a[i] = b[s[i]];
	dp[0] = 0, h = 1, t = 1, s[t] = 0;
	for (register int i = 1; i <= n; ++i){
		while (h < t && Y(s[h], s[h + 1]) * (-a[i].r) <= X(s[h], s[h + 1])) ++h;
		dp[i] = val(i, s[h]);
		while (h < t && Y(s[t - 1], s[t]) * X(s[t], i) >= Y(s[t], i) * X(s[t - 1], s[t])) --t;
		s[++t] = i;
	}
	printf("%lld\n", dp[n]);
}