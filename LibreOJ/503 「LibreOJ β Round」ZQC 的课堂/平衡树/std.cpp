#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 100005;
int n, q, x[N], y[N];
unsigned int rnd(){
	static unsigned int seed = 19260817;
	return seed ^= seed << 19, seed ^= seed >> 7, seed ^= seed << 1;
}
struct treap{
	unsigned int key[N];
	int top, rub[N], rt, cnt, val[N], sz[N], ls[N], rs[N];
	treap(){ cnt = top = 0; }
	int new_node(int v){
		int u = top ? rub[top--] : ++cnt;
		return val[u] = v, key[u] = rnd(), sz[u] = 1, ls[u] = rs[u] = 0, u;
	}
	void up(int u){ sz[u] = sz[ls[u]] + sz[rs[u]] + 1; }
	std :: pair<int, int> split_v(int u, int v){ // one is < v and another is >= v
		if (!u) return {0, 0};
		std :: pair<int, int> tmp;
		if (val[u] >= v) return tmp = split_v(ls[u], v), ls[u] = tmp.second, up(tmp.second = u), tmp;
		else return tmp = split_v(rs[u], v), rs[u] = tmp.first, up(tmp.first = u), tmp;
	}
	std :: pair<int, int> split_sz(int u, int k){
		if (!u) return {0, 0};
		std :: pair<int, int> tmp;
		if (sz[ls[u]] >= k) return tmp = split_sz(ls[u], k), ls[u] = tmp.second, up(tmp.second = u), tmp;
		return tmp = split_sz(rs[u], k - sz[ls[u]] - 1), rs[u] = tmp.first, up(tmp.first = u), tmp;
	}
	int merge(int u, int v){
		if (!u || !v) return u | v;
		if (key[u] < key[v]) return rs[u] = merge(rs[u], v), up(u), u;
		else return ls[v] = merge(u, ls[v]), up(v), v;
	}
	void insert(int v){
		std :: pair<int, int> tmp = split_v(rt, v + 1);
		rt = merge(merge(tmp.first, new_node(v)), tmp.second);
	}
	void erase(int v){
		std :: pair<int, int> tmp = split_v(rt, v), ttmp = split_sz(tmp.second, 1);
		rt = merge(tmp.first, ttmp.second), rub[++top] = ttmp.first;
	}
	int rnk(int v){
		int u = rt, res = 0;
		while (u) if (val[u] >= v) u = ls[u]; else res += sz[ls[u]] + 1, u = rs[u];
		return res;
	}
};
struct prefix_set{
	int p, d, s[N], sum, *a;
	treap mn, mx;
	void init(int *_a){
		sum = 0, d = 0, s[0] = 1, p = 1, a = _a;
		for (register int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
		for (register int i = 1; i < n; ++i)
			mn.insert(std :: min(s[i], s[i + 1])), mx.insert(std :: max(s[i], s[i + 1]));
	}
	void go_left(){
		if (p == 1) return;
		--p;
		if (1ll * s[p - 1] * s[p] > 0) --sum;
		s[p] -= d;
		mn.insert(std :: min(s[p], s[p + 1])), mx.insert(std :: max(s[p], s[p + 1]));
	}
	void go_right(){
		if (p == n) return;
		mn.erase(std :: min(s[p], s[p + 1])), mx.erase(std :: max(s[p], s[p + 1]));
		s[p] += d;
		if (1ll * s[p - 1] * s[p] > 0) ++sum;
		++p;
	}
	void modify(int v){ d += v - a[p], a[p] = v; }
	int query(){
		return n - 1 - sum - (n - p - mn.rnk(-d) + mx.rnk(-d)) + (1ll * s[p - 1] * (s[p] + d) < 0);
	}
}Sx, Sy;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) x[i] = read(), y[i] = read();
	Sx.init(x), Sy.init(y);
	q = read();
	while (q--){
		char op;
		while (!isalpha(op = getchar())) ;
		if (op == 'B') Sx.go_left(), Sy.go_left();
		if (op == 'F') Sx.go_right(), Sy.go_right();
		if (op == 'C') Sx.modify(read()), Sy.modify(read());
		if (op == 'Q') print(Sx.query() + Sy.query());
	}
}
