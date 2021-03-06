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
	int kth(int k){
		int u = rt;
		while (u)
			if (k <= sz[ls[u]]) u = ls[u];
			else if (k == sz[ls[u]] + 1) return val[u];
			else k -= sz[ls[u]] + 1, u = rs[u];
		return -1;
	}
	int pre(int v){
		int u = rt, res = -1;
		while (u) if (val[u] >= v) u = ls[u]; else res = val[u], u = rs[u];
		return res;
	}
	int nxt(int v){
		int u = rt, res = -1;
		while (u) if (val[u] <= v) u = rs[u]; else res = val[u], u = ls[u];
		return res;
	}
}T;
int main(){
	int n = read();
	while (n--){
		int opt = read(), x = read();
		if (opt == 1) T.insert(x);
		if (opt == 2) T.erase(x);
		if (opt == 3) print(T.rnk(x) + 1);
		if (opt == 4) print(T.kth(x));
		if (opt == 5) print(T.pre(x));
		if (opt == 6) print(T.nxt(x));
	}
}
