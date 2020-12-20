#include <bits/stdc++.h>

const int N = 50005, B = 225;

int n, q;
int a[N];
int tot, L[N], R[N], bel[N];

struct Query {
	int l, r, bl, id;

	bool operator < (const Query &rhs) const {
		if (bl != rhs.bl) {
			return bl < rhs.bl;
		}
		return r < rhs.r;
	}
} Q[N];

struct List {
	int ans;
	int L[N], R[N];
	int top, sta[N];

	void init(int n) {
		for (int i = 0; i <= n; ++i) {
			R[i] = i + 1;
			L[i + 1] = i;
		}
		ans = 0;
		top = 0;
	}

	void erase(int x) {
		ans = std::max(ans, R[x] - L[x] - 1);
		L[R[x]] = L[x];
		R[L[x]] = R[x];
		sta[++top] = x;
	}

	void undo() {
		int x = sta[top--];
		L[R[x]] = x;
		R[L[x]] = x;
	}
} T, _T;

int ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	tot = (n - 1) / B + 1;
	for (int i = 1; i <= tot; ++i) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(n, i * B);
		for (int j = L[i]; j <= R[i]; ++j) {
			bel[j] = i;
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].l >> Q[i].r;
		Q[i].bl = bel[Q[i].l];
		Q[i].id = i;
	}
	std::sort(Q + 1, Q + 1 + q);

	T.init(n), _T.init(n);
	int l = 1, r = 0, lst = 0;
	for (int i = 1; i <= q; ++i) {
		if (bel[Q[i].l] == bel[Q[i].r]) {
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				_T.erase(a[j]);
			}
			ans[Q[i].id] = _T.ans;
			while (_T.top) {
				_T.undo();
			}
			_T.ans = 0;
			continue;
		}
		if (bel[Q[i].l] != lst) {
			lst = bel[Q[i].l];
			r = R[lst], l = r + 1;
			while (T.top) {
				T.undo();
			}
			T.ans = 0;
		}
		while (r < Q[i].r) {
			T.erase(a[++r]);
		}
		int tmp = T.ans;
		while (l > Q[i].l) {
			T.erase(a[--l]);
		}
		ans[Q[i].id] = T.ans;
		while (l < R[lst] + 1) {
			T.undo();
			++l;
		}
		T.ans = tmp;
	}
	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}
