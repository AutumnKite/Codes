#include <bits/stdc++.h>

class basis {
	const int B = 18;

	std::vector<int> a;

public:
	basis() : a(B) {}

	bool insert(int x) {
		for (int i = B - 1; i >= 0; --i) {
			if (x >> i & 1) {
				if (!a[i]) {
					a[i] = x;
					return true;
				}
				x ^= a[i];
			}
		}
		return false;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	basis B;
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		if (B.insert(x)) {
			v.push_back(x);
		}
	}
	std::cout << v.size() << "\n";
	for (int i = 0; i < (int)(1 << v.size()); ++i) {
		int S = i ^ (i >> 1);
		int t = 0;
		for (int j = 0; j < (int)v.size(); ++j) {
			if (S >> j & 1) {
				t ^= v[j];
			}
		}
		std::cout << t << " ";
	}
	std::cout << "\n";
}