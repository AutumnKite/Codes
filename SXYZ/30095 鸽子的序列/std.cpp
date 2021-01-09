#include <bits/stdc++.h>

int n, q, T;

namespace Sub1 {
	const int N = 100005, B = 1500, C = N / B + 5;

	int mx, a[N];

	int tot, L[C], R[C], bel[N];
	int id[N], val[N];

	int cov[C];

	bool cmp(int x, int y) {
		return a[x] < a[y];
	}

	void down(int k) {
		if (!cov[k]) {
			return;
		}
		for (int i = L[k]; i <= R[k]; ++i) {
			a[i] = cov[k];
			val[i] = cov[k];
		}
		cov[k] = 0;
	}

	void resort(int b, int l, int r, int v) {
		down(b);
		static int t1[B + 5], t2[B + 5];
		int c1 = 0, c2 = 0;
		for (int i = L[b]; i <= R[b]; ++i) {
			if (l <= id[i] && id[i] <= r) {
				t1[++c1] = id[i];
				a[id[i]] = v;
			} else {
				t2[++c2] = id[i];
			}
		}
		std::merge(t1 + 1, t1 + c1 + 1, t2 + 1, t2 + c2 + 1, id + L[b], cmp);
		for (int i = L[b]; i <= R[b]; ++i) {
			val[i] = a[id[i]];
		}
	}

	int sum[N];

	void get_sum(int b, int l, int r) {
		down(b);
		int now = 0;
		for (int i = L[b]; i <= R[b]; ++i) {
			now += l <= id[i] && id[i] <= r;
			sum[i] = now;
		}
	}

	void Main() {
		for (int i = 1; i <= n; ++i) {
			std::cin >> a[i];
			mx = std::max(mx, a[i]);
		}

		tot = (n - 1) / B + 1;
		for (int i = 1; i <= tot; ++i) {
			L[i] = (i - 1) * B + 1;
			R[i] = std::min(i * B, n);
			cov[i] = 0;
			for (int j = L[i]; j <= R[i]; ++j) {
				bel[j] = i;
				id[j] = j;
			}
			std::sort(id + L[i], id + R[i] + 1, cmp);
			for (int j = L[i]; j <= R[i]; ++j) {
				val[j] = a[id[j]];
			}
		}

		int ans = 0;
		while (q--) {
			ans *= T;
			int op;
			std::cin >> op;
			if (op == 1) {
				int l, r, v;
				std::cin >> l >> r >> v;
				l ^= ans, r ^= ans, v ^= ans;
				int bl = bel[l], br = bel[r];
				mx = std::max(mx, v);
				if (bl == br) {
					resort(bl, l, r, v);
				} else {
					resort(bl, l, R[bl], v);
					resort(br, L[br], r, v);
					for (int i = bl + 1; i < br; ++i) {
						cov[i] = v;
					}
				}
			} else {
				int l, r, k;
				std::cin >> l >> r >> k;
				l ^= ans, r ^= ans, k ^= ans;
				int bl = bel[l], br = bel[r];
				if (bl == br) {
					get_sum(bl, l, r);
					for (int i = L[bl]; i <= R[bl]; ++i) {
						if (sum[i] == k) {
							std::cout << a[id[i]] << "\n";
							ans = a[id[i]];
							break;
						}
					}
				} else {
					get_sum(bl, l, R[bl]);
					get_sum(br, L[br], r);
					int l = 1, r = mx;
					while (l <= r) {
						int mid = (l + r) >> 1;
						int cnt = 0;
						for (int i = bl + 1; i < br; ++i) {
							if (cov[i]) {
								if (cov[i] <= mid) {
									cnt += R[i] - L[i] + 1;
								}
							} else {
								cnt += std::upper_bound(val + L[i], val + R[i] + 1, mid) - val - L[i];
							}
						}
						int pl = std::upper_bound(val + L[bl], val + R[bl] + 1, mid) - val - 1;
						cnt += pl < L[bl] ? 0 : sum[pl];
						int pr = std::upper_bound(val + L[br], val + R[br] + 1, mid) - val - 1;
						cnt += pr < L[br] ? 0 : sum[pr];
						if (k <= cnt) {
							ans = mid;
							r = mid - 1;
						} else {
							l = mid + 1;
						}
					}
					std::cout << ans << "\n";
				}
			}
		}
	}
}

namespace Sub2 {
	const int N = 500005, QC = N * 6;

	int mx, a[N];

	int tot;

	struct Query {
		int l, r, v, id;

		Query() {}

		Query(int _l, int _r, int _v, int _id) : l(_l), r(_r), v(_v), id(_id) {}
	} Q[QC];

	int c[N], ci[N];

	inline void add(register int x, register int v) {
		register int t = v * x;
		for (; x <= n; x += x & -x) {
			c[x] += v;
			ci[x] += t;
		}
	}

	inline int query(register int x) {
		register int t = x + 1;
		register int s = 0, si = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
			si += ci[x];
		}
		return s * t - si;
	}

	inline void add(int l, int r, int v) {
		add(l, v), add(r + 1, -v);
	}

	inline int query(int l, int r) {
		return query(r) - query(l - 1);
	}

	int ans[N];

	void solve(int l, int r, int L, int R) {
		if (l > r) {
			return;
		}
		if (L == R) {
			for (int i = l; i <= r; ++i) {
				if (Q[i].id > 0) {
					ans[Q[i].id] = L;
				}
			}
			return;
		}
		int mid = (L + R) >> 1;
		static int p1[QC], p2[QC];
		int c1 = 0, c2 = 0;
		for (int i = l; i <= r; ++i) {
			if (Q[i].id <= 0) {
				if (Q[i].v <= mid) {
					add(Q[i].l, Q[i].r, Q[i].id == 0 ? 1 : -1);
					p1[++c1] = i;
				} else {
					p2[++c2] = i;
				}
			} else {
				int cnt = query(Q[i].l, Q[i].r);
				if (Q[i].v <= cnt) {
					p1[++c1] = i;
				} else {
					Q[i].v -= cnt;
					p2[++c2] = i;
				}
			}
		}
		for (int i = l; i <= r; ++i) {
			if (Q[i].id <= 0 && Q[i].v <= mid) {
				add(Q[i].l, Q[i].r, Q[i].id == 0 ? -1 : 1);
			}
		}
		static Query tmp[QC];
		for (int i = 1; i <= c1; ++i) {
			tmp[l + i - 1] = Q[p1[i]];
		}
		for (int i = 1; i <= c2; ++i) {
			tmp[l + c1 + i - 1] = Q[p2[i]];
		}
		for (int i = l; i <= r; ++i) {
			Q[i] = tmp[i];
		}
		solve(l, l + c1 - 1, L, mid);
		solve(l + c1, r, mid + 1, R);
	}

	void Main() {
		std::map<int, int> S;
		for (int i = 1; i <= n; ++i) {
			std::cin >> a[i];
			mx = std::max(mx, a[i]);
			S[i] = a[i];
			Q[++tot] = Query(i, i, a[i], 0);
		}
		for (int i = 1; i <= q; ++i) {
			int op;
			std::cin >> op;
			if (op == 1) {
				int l, r, v;
				std::cin >> l >> r >> v;
				mx = std::max(mx, v);
				auto it = S.lower_bound(l);
				auto ed = S.upper_bound(r);
				int tmp = it->second;
				int lst = l - 1;
				while (it != ed) {
					Q[++tot] = Query(lst + 1, it->first, it->second, -1);
					lst = it->first;
					auto It = it;
					++it;
					S.erase(It);
				}
				if (lst < r) {
					Q[++tot] = Query(lst + 1, r, it->second, -1);
				}
				if (l > 1 && !S.count(l - 1)) {
					S[l - 1] = tmp;
				}
				S[r] = v;
				Q[++tot] = Query(l, r, v, 0);
			} else {
				int l, r, k;
				std::cin >> l >> r >> k;
				Q[++tot] = Query(l, r, k, i);
			}
			ans[i] = -1;
		}

		std::cerr << tot << "\n";

		solve(1, tot, 1, mx + 1);
		for (int i = 1; i <= q; ++i) {
			if (ans[i] != -1) {
				std::cout << ans[i] << "\n";
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q >> T;
	if (T == 0) {
		Sub2::Main();
	} else {
		Sub1::Main();
	}
}
