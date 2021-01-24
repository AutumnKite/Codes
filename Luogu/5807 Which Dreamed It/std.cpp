#include <bits/stdc++.h>

const int P = 1000003;

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

void dec(int &a, int b) {
	a < b ? a += P - b : a -= b;
}

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

int fac[200005];

void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
}

typedef std::vector<std::vector<int>> matrix;

int n;

int det(matrix a) {
	int n = a.size();
	int res = 1;
	for (int i = 0; i < n; ++i) {
		int k = -1;
		for (int j = i; j < n; ++j) {
			if (a[j][i]) {
				k = j;
			}
		}
		if (k == -1) {
			return 0;
		}
		if (k != i) {
			a[i].swap(a[k]);
			res = (P - res) % P;
		}
		int inv_a = qpow(a[i][i], P - 2);
		for (int j = i + 1; j < n; ++j) {
			int t = 1ll * (P - a[j][i]) * inv_a % P;
			for (int k = i; k < n; ++k) {
				a[j][k] = (a[j][k] + 1ll * t * a[i][k]) % P;
			}
		}
		res = 1ll * res * a[i][i] % P;
	}
	return res;
}

void solve() {
	std::cin >> n;
	std::vector<int> in(n), out(n);
	matrix A(n, std::vector<int>(n, 0));
	int m = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> out[i];
		for (int j = 0; j < out[i]; ++j) {
			int k;
			std::cin >> k;
			--k;
			++in[k];
			dec(A[i][k], 1);
		}
		inc(A[i][i], out[i]);
		m += out[i];
	}

	for (int i = 0; i < n; ++i) {
		if (in[i] != out[i]) {
			std::cout << 0 << "\n";
			return;
		}
	}
	
	if (!out[0]) {
		if (m) {
			std::cout << 0 << "\n";
		} else {
			std::cout << 1 << "\n";
		}
		return;
	}

	std::vector<int> id;
	for (int i = 1; i < n; ++i) {
		if (out[i]) {
			id.push_back(i);
		}
	}
	
	matrix H(id.size(), std::vector<int>(id.size()));
	for (int i = 0; i < (int)id.size(); ++i) {
		for (int j = 0; j < (int)id.size(); ++j) {
			H[i][j] = A[id[i]][id[j]];
		}
	}

	int ans = det(H);
	for (int i = 0; i < n; ++i) {
		if (out[i]) {
			ans = 1ll * ans * fac[out[i] - 1] % P;
		}
	}
	std::cout << 1ll * ans * out[0] % P << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T = 1;
	std::cin >> T;
	init(200000);
	while (T--) {
		solve();
	}
}