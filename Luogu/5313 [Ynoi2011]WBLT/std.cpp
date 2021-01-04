#include <bits/stdc++.h>

// #define DEBUG

const int N = 100005, W = 40, B = 4000;

int n, q, m;
int a[N];

int cq;

struct Query {
	int l, r, b, bl, id;

	bool operator < (const Query &rhs) const {
		if (bl != rhs.bl) {
			return bl < rhs.bl;
		}
		if (bl & 1) {
			return r < rhs.r;
		} else {
			return r > rhs.r;
		}
	}
} Q[N];

std::vector<Query> R[W];

int ans[N];

int cnt[N];

struct Bitset {
	static const int N = ::N / 64 + 5;

	int sz;
	unsigned long long c[N];

	inline void set(int _sz) {
		sz = _sz >> 6;
		for (int i = 0; i < sz; ++i) {
			c[i] = ~0ull;
		}
		c[sz] = (1ull << (_sz & 63)) - 1;
		c[sz + 1] = 0;
	}

	inline void reset(int _sz) {
		sz = _sz >> 6;
		std::fill(c, c + sz + 2, 0);
	}

	inline void flip(int x) {
		c[x >> 6] ^= 1ull << (x & 63);
	}

	inline bool bit_and(const Bitset &A, register int l) {
		register int t = l & 63, tt = 64 - t;
		l >>= 6;
		register int len = std::min(sz, A.sz - l);
		register bool flag = 1;
		if (t) {
			for (register int i = 0; i <= len; ++i) {
				c[i] &= A.c[l + i] >> t | A.c[l + i + 1] << tt;
				flag &= !c[i];
			}
		} else {
			for (register int i = 0; i <= len; ++i) {
				c[i] &= A.c[l + i];
				flag &= !c[i];
			}
		}
		return flag;
	}

	inline int find0() {
		for (register int i = 0; i <= sz; ++i) {
			if (c[i] != ~0ull) {
				return i << 6 | __builtin_ctzll(~c[i]);
			}
		}
		return sz;
	}
} now, tmp, pos[W];

inline void add(register int v) {
	if (!cnt[v]) {
		now.flip(v);
	}
	++cnt[v];
}

inline void del(register int v) {
	--cnt[v];
	if (!cnt[v]) {
		now.flip(v);
	}
}

#ifdef DEBUG
std::mt19937 rnd(233333);
#endif

int main() {
#ifdef DEBUG
	freopen("bdcmd.out", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

#ifdef DEBUG
	n = 100000;
#else
	std::cin >> n;
#endif
	for (int i = 1; i <= n; ++i) {
#ifdef DEBUG
		a[i] = rnd() % 100001;
#else
		std::cin >> a[i];
#endif
		m = std::max(m, a[i] + 1);
	}
#ifdef DEBUG
	q = 100000;
#else
	std::cin >> q;
#endif
	for (int i = 1; i <= q; ++i) {
		Query tmp;
#ifdef DEBUG
		tmp.l = rnd() % n + 1;
		tmp.r = rnd() % n + 1;
		if (tmp.l > tmp.r) {
			std::swap(tmp.l, tmp.r);
		}
		if (rnd() & 1) {
			tmp.b = rnd() % W + 1;
		} else {
			tmp.b = rnd() % 100000 + 1;
		}
#else
		std::cin >> tmp.l >> tmp.r >> tmp.b;
#endif
		tmp.b = std::min(tmp.b, m);
		tmp.bl = (tmp.l - 1) / B + 1;
		tmp.id = i;
		if (tmp.b >= W) {
			Q[++cq] = tmp;
		} else {
			R[tmp.b].push_back(tmp);
		}
	}
	
	std::sort(Q + 1, Q + 1 + cq);
	now.reset(m);
	register int l = 1, r = 0;
	for (register int i = 1; i <= cq; ++i) {
		while (l > Q[i].l) {
			add(a[--l]);
		}
		while (r < Q[i].r) {
			add(a[++r]);
		}
		while (l < Q[i].l) {
			del(a[l++]);
		}
		while (r > Q[i].r) {
			del(a[r--]);
		}
		tmp.set(Q[i].b);
		register int t = 0;
		while (1) {
			if (!tmp.bit_and(now, t * Q[i].b)) {
				++t;
			} else {
				break;
			}
		}
		ans[Q[i].id] = t;
	}
#ifdef DEBUG
	std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << "\n";
#endif
	for (register int k = 1; k < W; ++k) {
		for (register int i = 0; i < m; ++i) {
			cnt[i] = 0;
		}
		for (register int i = 0; i < k; ++i) {
			pos[i].reset((m - 1) / k + 1);
		}
		auto add = [&](register int v) {
			if (!cnt[v]) {
				pos[v % k].flip(v / k);
			}
			++cnt[v];
		};
		auto del = [&](register int v) {
			--cnt[v];
			if (!cnt[v]) {
				pos[v % k].flip(v / k);
			}
		};
		std::sort(R[k].begin(), R[k].end());
		register int l = 1, r = 0;
		for (auto v : R[k]) {
			while (l > v.l) {
				add(a[--l]);
			}
			while (r < v.r) {
				add(a[++r]);
			}
			while (l < v.l) {
				del(a[l++]);
			}
			while (r > v.r) {
				del(a[r--]);
			}
			register int t = 0;
			for (register int i = 0; i < k; ++i) {
				t = std::max(t, pos[i].find0());
			}
			ans[v.id] = t;
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
#ifdef DEBUG
	std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << "\n";
#endif
}