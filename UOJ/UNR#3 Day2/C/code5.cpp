#include <bits/stdc++.h>

using namespace std;

namespace io {
const int L = (1 << 19) + 1;
char ibuf[L], *iS, *iT, obuf[L], *oS = obuf, *oT = obuf + L - 1, c, st[55];
int f, tp;
char gc() {
	if (iS == iT) {
		iT = (iS = ibuf) + fread(ibuf, 1, L, stdin);
		return iS == iT ? EOF : *iS++;
	}
	return *iS++;
}
void cbuf() {
	fwrite(obuf, 1, oS - obuf, stdout);
	oS = obuf;
}
void putc(char x) {
	*oS++ = x;
	if (oS == oT) cbuf();
}
void gs(char *s) {
	for (c = gc(); c < 'a' || c > 'z'; c = gc())
		;
	for (; c >= 'a' && c <= 'z'; c = gc()) *s++ = c;
}
template <class I>
void gi(I &x) {
	for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
		if (c == '-') f = -1;
	for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
	x *= f;
}
template <class I>
void print(I x) {
	if (!x) putc('0');
	if (x < 0) putc('-'), x = -x;
	while (x) st[++tp] = x % 10 + '0', x /= 10;
	while (tp) putc(st[tp--]);
}
};
using io::putc;
using io::gi;
using io::gs;
using io::print;

const int N = 100005;
typedef long long ll;

struct rnd {
	unsigned seed;
	rnd() { seed = 19260817 ^ time(0) ^ size_t(new char); }
	unsigned operator()() {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		return seed;
	}
};
struct no {
	int l, r;
	bool operator<(const no &x) const { return l < x.l || (l == x.l && r > x.r); }
} a[N], b[N];
ll calc(const no &a, const no &b) {
	int mxl = max(a.l, b.l), mnr = min(a.r, b.r);
	if (mnr < mxl) return 0;
	int mxr = a.r + b.r - mnr, mnl = a.l + b.l - mxl;
	return (ll)(mxr - mnl) * (mnr - mxl);
}
int n, m, id[N];
ll ans, z[N], ret;
bool cmp(const int &x, const int &y) { return z[x] > z[y]; }
int main() {
	rnd rand;
	gi(n);
	int i, j, u, v, l, r, lmid, rmid;
	for (i = 1; i <= n; i++) gi(a[i].l), gi(a[i].r);
	sort(a + 1, a + n + 1);
	b[++m] = a[1];
	for (i = 2; i <= n; i++) {
		if (a[i].r > b[m].r)
			b[++m] = a[i];
		else
			ans = max(ans, calc(b[m], a[i]));
	}
	for (i = 1; i <= 1000000; i++) {
		u = rand() % m + 1, v = rand() % m + 1;
		if (u != v) ans = max(ans, calc(b[u], b[v]));
	}
	for (i = 2; i <= m; i++) {
		l = 1, r = i - 1, lmid = (2 * l + r) / 3, rmid = (l + 2 * r) / 3, ret = 0;
		while (r - l > 3) {
			ll w1 = calc(b[lmid], b[i]), w2 = calc(b[rmid], b[i]);
			if (w1 > w2)
				ret = max(ret, w1), r = (3 * r + l) >> 2;
			else
				ret = max(ret, w2), l = (3 * l + r) >> 2;
			lmid = (2 * l + r) / 3, rmid = (l + 2 * r) / 3;
		}
		for (j = l; j <= r; j++) ret = max(ret, calc(b[i], b[j]));
		z[i] = ret;
		ans = max(ans, ret);
	}
	for (i = 1; i <= m; i++) id[i] = i;
	nth_element(id + 1, id + min(m, 50), id + m + 1, cmp);
	for (i = 1; i <= m && clock() * 1.0 / CLOCKS_PER_SEC < 0.48; i++) {
		for (j = 1; j <= m; j++)
			if (j != id[i]) {
				ans = max(ans, calc(b[id[i]], b[j]));
			}
	}
	printf("%lld\n", ans);
	return 0;
}
