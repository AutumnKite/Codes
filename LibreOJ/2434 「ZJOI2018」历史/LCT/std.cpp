#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
char pbuf[1 << 23], *pp = pbuf;
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(long long x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 400005;
int n, q;
long long ans, a[N];
std::vector<int> E[N];
namespace LCT{
	int fa[N], son[N][2], wson[N];
	long long sum[N], lz[N], lst[N];
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
	void add(int u, long long w){
		if (u) sum[u] += w, lz[u] += w;
	}
	void down(int u){
		if (lz[u]) add(son[u][0], lz[u]), add(son[u][1], lz[u]), lz[u] = 0;
	}
	void change(int u, int k, int v){ son[u][k] = v, fa[v] = u; }
	void rotate(int u){
		int v = fa[u], d = dir(u);
		change(v, d, son[u][!d]);
		if (!is_root(v)) change(fa[v], dir(v), u); else fa[u] = fa[v];
		change(u, !d, v);
	}
	int tp, sta[N];
	void splay(int u){
		tp = 1, sta[tp] = u;
		for (register int i = u; !is_root(i); i = fa[i]) sta[++tp] = fa[i];
		while (tp) down(sta[tp]), --tp;
		while (!is_root(u)){
			int v = fa[u];
			if (is_root(v)){ rotate(u); continue; }
			dir(u) == dir(v) ? rotate(v) : rotate(u), rotate(u);
		}
	}
	int get_tp(int u){
		splay(u);
		while (son[u][0]) down(u), u = son[u][0];
		return splay(u), u;
	}
	long long calc(int u){
		if (wson[u]){
			if (wson[u] != u) return 2 * (sum[u] - sum[wson[u]]);
			else return 2 * (sum[u] - a[u]);
		}
		else return sum[u] - 1;
	}
	void access(int u, int w){
		splay(u), ans -= lst[u], sum[u] += w, add(son[u][0], w), a[u] += w;
		if (wson[u] != u){
			if (2 * a[u] > sum[u]) son[u][1] = 0, wson[u] = u;
			else if (wson[u]){
				splay(wson[u]), splay(u);
				if (2 * sum[wson[u]] <= sum[u])	son[u][1] = 0, wson[u] = 0;
			}
		}
		ans += lst[u] = calc(u);
		// printf("%lld\n", ans);
		int v = u;
		u = fa[u], v = get_tp(v);
		while (u){
			// fprintf(stderr, "u=%d v=%d\n", u, v);
			splay(u), ans -= lst[u], sum[u] += w, add(son[u][0], w);
			if (2 * sum[v] > sum[u]) wson[u] = v, son[u][1] = v;
			else if (wson[u]){
				if (wson[u] == u && 2 * a[u] <= sum[u]) son[u][1] = 0, wson[u] = 0;
				else if (wson[u] != u){
					// fprintf(stderr, "%d %d\n", wson[u], u);
					splay(wson[u]), splay(u);
					if (2 * sum[wson[u]] <= sum[u]) son[u][1] = 0, wson[u] = 0;
				}
			}
			ans += lst[u] = calc(u);
			v = u, u = fa[u], v = get_tp(v);
		}
	}
	void build(int u){
		sum[u] = a[u], lz[u] = 0, son[u][0] = son[u][1] = 0, wson[u] = 0;
		for (register int i = 0, v; i < (int)E[u].size(); ++i)
			if ((v = E[u][i]) != fa[u]) fa[v] = u, build(v), sum[u] += sum[v];
		if (2 * a[u] > sum[u]) wson[u] = u;
		for (register int i = 0, v; i < (int)E[u].size(); ++i)
			if ((v = E[u][i]) != fa[u] && 2 * sum[v] > sum[u]) wson[u] = v;
		if (wson[u] && wson[u] != u) son[u][1] = wson[u];
		ans += lst[u] = calc(u);
	}
}
int main(){
	// freopen("history.in", "r", stdin);
	// freopen("history.out", "w", stdout);
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	ans = 0, LCT::build(1);
	print(ans);
	while (q--){
		int x = read(), w = read();
		LCT::access(x, w), print(ans);
		// fprintf(stderr, "%d\n", q);
	}
}

/*
 * 獃滏叢槑懮蓿䆩
 */
