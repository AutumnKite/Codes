#include <bits/stdc++.h> // hje AK IOI
int n, A, B, a[55], b[55], dp[55][10005];
void cmx(int &x, int y){ x = std :: max(x, y); }
int main(){
	scanf("%d%d%d", &n, &B, &A), B += A;
	for (register int i = 1; i <= n; ++i) scanf("%d%d", b + i, a + i), b[i] += a[i];
	memset(dp, -1, sizeof dp), dp[0][0] = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i - 1; ~j; --j)
			for (register int k = 0; k <= A; ++k)
				if (~dp[j][k]) cmx(dp[j + 1][k + a[i] > A ? A : k + a[i]], dp[j][k] + b[i]);
	for (register int i = 1; i <= n; ++i) if (dp[i][A] >= B) return printf("%d\n", i), 0;
	return printf("-1\n"), 0;
}
