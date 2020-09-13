#include <bits/stdc++.h>

#define debug(...) fprintf(stderr, __VA_ARGS__)

const int N = 100005;

int n, B, vis[N], cnt, p[N];

int X, tot;
bool ex[N];

int Query(int v) {
	// printf("B %d\n", v);
	// fflush(stdout);
	// int x;
	// scanf("%d", &x);
	// return x;
	int x = 0;
	for (int i = v; i <= n; i += v) {
		x += ex[i];
		if (i != X) {
			ex[i] = 0;
		}
	}
	++tot;
	return x;
}

void solve() {
	scanf("%d", &n);
	scanf("%d", &X);
	for (int i = 1; i <= n; ++i) {
		ex[i] = 1;
	}
	B = sqrt(n);
	while (B * B < n) {
		++B;
	}
	for (int i = 1; i <= n; ++i) {
		vis[i] = 1;
	}
	cnt = 0;
	vis[1] = 0;
	for (int i = 2; i <= n; ++i) {
		if (vis[i]) {
			p[++cnt] = i;
			if (i <= B) {
				Query(i);
			}
			for (int j = i + i; j <= n; j += i) {
				vis[j] = 0;
			}
		}
	}
	int ans = 1;
	for (int i = 1; i <= cnt; ++i) {
		while (1ll * ans * p[i] <= n) {
			if (Query(ans) == 1) {
				ans *= p[i];
			} else {
				break;
			}
		}
	}
	printf("C %d\n", ans);
	fflush(stdout);
	printf("total: %d\n", tot);
}

int main() {
	int T = 1;
	// read(T);
	while (T--) {
		solve();
	}
}