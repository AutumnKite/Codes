#include <bits/stdc++.h>

const int N = 105;
const int P = 1000000007;
const int B = 15, M = (1 << B) - 1;

int n;
int tp, h[N];

int pw[1 << B], pwt[1 << B];

void init() {
	pw[0] = 1;
	for (int i = 1; i <= M; ++i) {
		pw[i] = 2 * pw[i - 1] % P;
	}
	int t = 2 * pw[M] % P;
	pwt[0] = 1;
	for (int i = 1; i <= M; ++i) {
		pwt[i] = 1ll * pwt[i - 1] * t % P;
	}
}

int qpow(int b) {
	return 1ll * pwt[b >> B] * pw[b & M] % P;
}

struct State {
	int f, g;

	void merge(State r, int h) {
		int t = qpow(h);
		r.f = 1ll * r.f * t % P;
		g = (1ll * g * r.g + 2ll * f * r.g + 2ll * g * r.f + 2ll * f * r.f) % P;
		f = 1ll * f * r.f % P;
	}
} dp[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();
	std::cin >> n;
	tp = 0;
	for (int i = 1; i <= n; ++i) {
		int x;
		std::cin >> x;
		State tmp = {1, 0};
		while (tp && h[tp] >= x) {
			if (tp > 1 && h[tp - 1] >= x) {
				dp[tp - 1].merge(dp[tp], h[tp] - h[tp - 1]);
			} else {
				tmp.merge(dp[tp], h[tp] - x);
			}
			--tp;
		}
		dp[++tp] = tmp;
		h[tp] = x;
	}
	while (tp > 1) {
		dp[tp - 1].merge(dp[tp], h[tp] - h[tp - 1]);
		--tp;
	}
	std::cout << (dp[1].g + 1ll * dp[1].f * qpow(h[1])) % P << std::endl;
}