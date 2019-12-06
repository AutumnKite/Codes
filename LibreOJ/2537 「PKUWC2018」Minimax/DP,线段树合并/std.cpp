#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
// char buf[1 << 23], *ps = buf, *pt = buf;
// #define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 300005, P = 998244353, Inv = 796898467;
int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int n, m, ls[N], rs[N], rt[N], p[N], ans;
struct Segment_Tree{
	int cnt, ls[N * 30], rs[N * 30];
	int val[N * 30], lz[N * 30];
	void insert(int &u, int l, int r, int x, int v){
		u = ++cnt, ls[u] = rs[u] = 0, lz[u] = 1, val[u] = v;
		if (l == r) return;
		int md = (l + r) >> 1;
		if (x <= md) insert(ls[u], l, md, x, v);
		else insert(rs[u], md + 1, r, x, v);
	}
	void mul(int u, int v){
		val[u] = 1ll * val[u] * v % P, lz[u] = 1ll * lz[u] * v % P;
	}
	void down(int u){
		if (ls[u]) mul(ls[u], lz[u]);
		if (rs[u]) mul(rs[u], lz[u]);
		lz[u] = 1;
	}
	int merge(int u1, int u2, int s1, int s2, int p){
		if (!u1 && !u2) return 0;
		if (!u2) return mul(u1, (1ll * p * minus(1, s2) + 1ll * minus(1, p) * s2) % P), u1;
		if (!u1) return mul(u2, (1ll * p * minus(1, s1) + 1ll * minus(1, p) * s1) % P), u2;
		down(u1), down(u2);
		ls[u1] = merge(ls[u1], ls[u2], plus(s1, val[rs[u1]]), plus(s2, val[rs[u2]]), p);
		rs[u1] = merge(rs[u1], rs[u2], s1, s2, p);
		val[u1] = plus(val[ls[u1]], val[rs[u1]]);
		return u1;
	}
	int get_ans(int u, int l, int r, int c){
		if (l == r) return ans = (ans + 1ll * c * l % P * val[u] % P * val[u]) % P, 1;
		int md = (l + r) >> 1, t = 0;
		if (ls[u]) t += get_ans(ls[u], l, md, c);
		if (rs[u]) t += get_ans(rs[u], md + 1, r, c + t);
		return t;
	}
}T;
void dfs(int u){
	if (!ls[u]) return T.insert(rt[u], 1, m, p[u], 1), void(0);
	if (!rs[u]) return dfs(ls[u]), rt[u] = rt[ls[u]], void(0);
	dfs(ls[u]), dfs(rs[u]), rt[u] = T.merge(ls[u], rs[u], 0, 0, p[u]);
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i){
		int fa = read();
		if (!fa) continue;
		if (ls[fa]) rs[fa] = i; else ls[fa] = i;
	}
	for (register int i = 1; i <= n; ++i){
		p[i] = read();
		if (ls[i]) p[i] = 1ll * p[i] * Inv % P;
		else m = std :: max(m, p[i]);
	}
	dfs(1);
	T.get_ans(rt[1], 1, m, 1);
	printf("%d\n", ans);
}
