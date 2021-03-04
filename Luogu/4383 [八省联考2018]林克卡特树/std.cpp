#include <bits/stdc++.h>

const int N = 300005;

int n, m;
std::vector<std::pair<int, int>> E[N];

struct State {
	long long v;
	int c;

	State() : v(0), c(0) {}
	State(long long _v, int _c) : v(_v), c(_c) {}

	State operator+(const State &rhs) const {
		return State(v + rhs.v, c + rhs.c);
	}

	bool operator<(const State &rhs) const {
		return v < rhs.v || (v == rhs.v && c < rhs.c);
	}
};

State f[N][3];

void dfs(long long K, int u, int fa = 0) {
	f[u][0] = f[u][1] = f[u][2] = State();
	for (auto p : E[u]) {
		int v = p.first;
		if (v != fa) {
			int w = p.second;
			dfs(K, v, u);
			f[u][2] = std::max(f[u][2] + std::max(f[v][0], f[v][2] + State(-K, 1)), f[u][1] + f[v][1] + State(w, 0));
			f[u][1] = std::max(f[u][1] + std::max(f[v][0], f[v][2] + State(-K, 1)), f[u][0] + f[v][1] + State(w, 0));
			f[u][0] = f[u][0] + std::max(f[v][0], f[v][2] + State(-K, 1));
		}
	}
}

State DP(long long K) {
	dfs(K, 1);
	return std::max(f[1][0], f[1][2] + State(-K, 1));
}

bool check(long long K) {
	return DP(K).c >= m;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	++m;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
	}

	long long l = -1e12, r = 1e12, ans = 0;
	while (l <= r) {
		long long mid = (l + r) / 2;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	std::cout << DP(ans).v + ans * m << "\n";
}
