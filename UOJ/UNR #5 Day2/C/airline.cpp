#include <bits/stdc++.h>

#include "airline.h"

long long query(int x, int y) {
	if (x == y) {
		return 0;
	}
	if (x > y) {
		std::swap(x, y);
	}
	static std::map<std::pair<int, int>, long long> mp;
	auto tmp = std::make_pair(x, y);
	if (mp.count(tmp)) {
		return mp[tmp];
	}
	return mp[tmp] = distance(x + 1, y + 1);
}

long long solve(int n, int x, int y, int q, std::vector<int> p, int L) {
	--x, --y;
	for (int &v : p) {
		--v;
	}
	p.insert(p.begin(), y);
	p.insert(p.begin(), x);
	q += 2;

	std::vector<long long> adj(q);
	for (int i = 1; i < q; ++i) {
		adj[i] = query(p[i - 1], p[i]);
	}
	std::vector<long long> sum(q);
	for (int i = 1; i < q; ++i) {
		sum[i] = sum[i - 1] + adj[i];
	}

	std::vector<long long> f(q);
	auto val = [&](int i, int j) {
		return f[j] + query(p[j - 1], p[i]) + sum[i - 1] - sum[j];
	};
	if (1ll * q * (q - 1) / 2 <= L) {
		for (int i = 2; i < q; ++i) {
			for (int j = 1; j < i; ++j) {
				f[i] = std::max(f[i], val(i, j));
			}
		}
	} else {
		int lst = 1;
		for (int i = 2; i < q; ++i) {
			for (int j = lst; j < i; ++j) {
				long long t = val(i, j);
				if (t > f[i]) {
					f[i] = t;
					lst = j;
				}
			}
		}
	}
	long long ans = 0;
	for (int i = q - 1; i > 0; --i) {
		ans = std::max(ans, f[i] + sum[q - 1] - sum[i]);
	}
	return ans;
}
