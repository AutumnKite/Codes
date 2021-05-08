#include <bits/stdc++.h>

struct Node {
	long long s, v;
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n, m, ds, dv;
	std::cin >> n >> m >> ds >> dv;
	std::vector<Node> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i].s >> a[i].v;
	}
	std::sort(a.begin(), a.end(), [&](Node x, Node y) {
		return x.s < y.s;
	});
	
	auto calc = [&](long long s, long long v) {
		return (dv == 1 ? v : v * v) - (ds == 1 ? s : s * s);
	};

	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		long long sum = 0;
		for (int j = 0; j < m && i - j >= 0; ++j) {
			sum += a[i - j].v;
			ans = std::max(ans, calc(a[i].s - a[i - j].s, sum));
		}
	}
	
	std::vector<int> l(n), r(n);
	std::vector<int> sta;
	sta.push_back(n);
	for (int i = 0; i < n; ++i) {
		while ((int)sta.size() > 1 && a[sta.back()].v < a[i].v) {
			sta.pop_back();
		}
		l[i] = sta.back();
		sta.push_back(i);
	}
	sta.clear();
	sta.push_back(n + 1);
	for (int i = n - 1; i >= 0; --i) {
		while ((int)sta.size() > 1 && a[sta.back()].v <= a[i].v) {
			sta.pop_back();
		}
		r[i] = sta.back();
		sta.push_back(i);
	}
	
	std::vector<int> p(n);
	for (int i = 0; i < n; ++i) {
		p[i] = i;
	}
	std::sort(p.begin(), p.end(), [&](int x, int y) {
		return a[x].v > a[y].v || (a[x].v == a[y].v && x < y);
	});
	std::vector<int> pr(n + 2, -1), nx(n + 2, -1);
	pr[n + 1] = n, nx[n] = n + 1;
	for (int i : p) {
		pr[r[i]] = i, nx[i] = r[i];
		nx[l[i]] = i, pr[i] = l[i];
		std::deque<int> Q;
		for (int j = 0, t = i; j < m && t != n; ++j) {
			Q.push_front(t);
			t = pr[t];
		}
		for (int j = 1, t = nx[i]; j < m && t != n + 1; ++j) {
			Q.push_back(t);
			t = nx[t];
		}
		if ((int)Q.size() < m) {
			continue;
		}
		auto L = Q.begin(), R = Q.begin();
		long long sum = 0;
		for (int j = 0; j < m - 1; ++j) {
			sum += a[*R].v;
			++R;
		}
		while (R != Q.end()) {
			sum += a[*R].v;
			ans = std::max(ans, calc(a[*R].s - a[*L].s, sum));
			++R;
			sum -= a[*L].v;
			++L;
		}
	}
	std::cout << ans << "\n";
}


