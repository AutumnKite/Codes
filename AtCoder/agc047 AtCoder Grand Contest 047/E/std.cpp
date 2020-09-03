#include <bits/stdc++.h>

std::pair<int, int> a;

struct Order {
	int op, i, j, k;
};

std::vector<Order> ans;

void mul(int x, int p) {
	for (int i = 1; i <= p; ++i) {
		ans.push_back({0, x, x, x});
	}
}

void split(int x, int st) {
	ans.push_back({0, x, 3, 93});
	ans.push_back({0, 96, 97, 94});
	for (int i = 29; ~i; --i) {
		ans.push_back({0, 94, i + 3, 95});
		ans.push_back({1, 95, 93, 95});
		ans.push_back({0, 95, 96, st + i});
		mul(95, i);
		ans.push_back({0, 94, 95, 94});
	}
}

void land(int x, int y, int st) {
	ans.push_back({0, x, y, st});
	ans.push_back({1, 3, st, st});
}

int main() {
	ans.push_back({0, 0, 1, 3});
	ans.push_back({0, 3, 3, 3});
	ans.push_back({1, 0, 3, 3});
	for (int i = 1; i < 30; ++i) {
		ans.push_back({0, i + 2, i + 2, i + 3});
	}
	split(0, 33), split(1, 63);
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			land(33 + i, 63 + j, 93);
			mul(93, i + j);
			ans.push_back({0, 2, 93, 2});
		}
	}
	printf("%d\n", (int)ans.size());
	for (auto v : ans) {
		printf("%c %d %d %d\n", v.op == 0 ? '+' : '<', v.i, v.j, v.k);
	}
}
