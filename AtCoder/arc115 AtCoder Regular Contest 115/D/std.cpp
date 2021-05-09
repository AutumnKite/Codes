#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int p, a, b;
	std::cin >> p >> a >> b;

	if (p == 2) {
		std::cout << "Yes\n";
		std::cout << 1 << " " << 1 << "\n";
		return 0;
	}

	auto len = [&](int x) {
		int now = 1, len = 0;
		do {
			now = 1ll * now * x % p;
			++len;
		} while (now != 1);
		return len;
	};

	if (len(a) & 1) {
		std::swap(a, b);
	}

	int l = len(a);

	if (l & 1) {
		std::cout << "No\n";
		return 0;
	}

	int invb = [&](int a, int b) {
		int s = 1;
		for (; b; b >>= 1) {
			if (b & 1) {
				s = 1ll * s * a % p;
			}
			a = 1ll * a * a % p;
		}
		return s;
	}(b, p - 2);

	std::vector<int> ans;
	int now = 1;
	for (int i = 0; i < l; i += 2) {
		for (int i = 0; i < (p - 1) / l; ++i) {
			ans.push_back(now);
			now = 1ll * now * b % p;
		}
		now = 1ll * now * invb % p * a % p;
		for (int i = 0; i < (p - 1) / l; ++i) {
			ans.push_back(now);
			now = 1ll * now * invb % p;
		}
		now = 1ll * now * b % p * a % p;
	}

	std::vector<bool> vis(p);
	for (int v : ans) {
		if (vis[v]) {
			std::cout << "No\n";
			return 0;
		}
		vis[v] = true;
	}

	if ((int)ans.size() != p - 1) {
		std::cout << "No\n";
	} else {
		std::cout << "Yes\n";
		for (int v : ans) {
			std::cout << v << " ";
		}
		std::cout << 1 << "\n";
	}
}
