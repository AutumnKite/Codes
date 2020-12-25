#include <bits/stdc++.h>

const int N = 100005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n;
long long L[N], R[N];
long long s[N], t[N];

struct Line {
	long long k, b;

	Line() {}
	Line(long long _k, long long _b) : k(_k), b(_b) {}

	long long get(long long x) {
		return k * x + b;
	}
};

struct LiChaoTree {
	int cnt, rt, ls[N], rs[N];
	Line val[N];

	void insert(int &u, long long l, long long r, Line v) {
		if (!u) {
			u = ++cnt;
			ls[u] = rs[u] = 0;
			val[u] = v;
			return;
		}
		if (val[u].get(l) <= v.get(l) && val[u].get(r) <= v.get(r)) {
			return;
		}
		if (v.get(l) <= val[u].get(l) && v.get(r) <= val[u].get(r)) {
			val[u] = v;
			return;
		}
		long long mid = (l + r) >> 1;
		if (v.get(mid) <= val[u].get(mid)) {
			std::swap(val[u], v);
		}
		if (v.get(l) <= val[u].get(l)) {
			insert(ls[u], l, mid, v);
		} else {
			insert(rs[u], mid + 1, r, v);
		}
	}

	long long query(int u, long long l, long long r, long long x) {
		if (!u) {
			return INF;
		}
		if (l == r) {
			return val[u].get(x);
		}
		long long mid = (l + r) >> 1;
		if (x <= mid) {
			return std::min(val[u].get(x), query(ls[u], l, mid, x));
		} else {
			return std::min(val[u].get(x), query(rs[u], mid + 1, r, x));
		}
	}
} Tmin, Tmax;

bool can[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> L[i] >> R[i];
		s[i] = s[i - 1] + (L[i] + R[i]) * (R[i] - L[i]);
		t[i] = t[i - 1] + 2 * (R[i] - L[i]);
	}

	for (int i = n; i; --i) {
		can[i] = -Tmax.query(Tmax.rt, 0, t[n], t[i]) <= -s[i] && -s[i] <= Tmin.query(Tmin.rt, 0, t[n], t[i]);
		Tmin.insert(Tmin.rt, 0, t[n], Line(-R[i], R[i] * t[i - 1] - s[i - 1]));
		Tmax.insert(Tmax.rt, 0, t[n], Line(L[i], s[i - 1] - L[i] * t[i - 1]));
	}

	int lst = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (can[i]) {
			ans = std::max(ans, i - lst);
			lst = i;
		}
	}
	std::cout << ans << "\n";
}