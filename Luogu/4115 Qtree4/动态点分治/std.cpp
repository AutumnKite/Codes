#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <queue>
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
char readc(){
	char c = getchar();
	while (!isalpha(c)) c = getchar();
	return c;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
void print_str(char *s, char ch = '\n'){
	int n = strlen(s);
	for (register int i = 0; i < n; ++i) putchar(s[i]);
	putchar(ch);
}
const int N = 1000005, INF = 0x3f3f3f3f;
int n, q, col[N], cnt_white;
int edge, to[N << 1], tw[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
int sum[N], dep[N], idx, dfn[N], st[N << 1][18], Log[N << 1];
void init_dfs(int u, int fa = 0){
	dep[u] = dep[fa] + 1, dfn[u] = ++idx, st[idx][0] = u;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa) sum[v] = sum[u] + tw[i], init_dfs(v, u), st[++idx][0] = u;
}
int Min(int x, int y){ return dep[x] < dep[y] ? x : y; }
void init(){
	idx = 0, init_dfs(1);
	Log[1] = 0;
	for (register int i = 2; i <= idx; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int j = 1; j <= 17; ++j)
		for (register int i = 1; i <= idx - (1 << j) + 1; ++i)
			st[i][j] = Min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int LCA(int l, int r){
	l = dfn[l], r = dfn[r];
	if (l > r) std :: swap(l, r);
	int t = Log[r - l + 1];
	return Min(st[l][t], st[r - (1 << t) + 1][t]);
}
int dist(int u, int v){
	return sum[u] + sum[v] - (sum[LCA(u, v)] << 1);
}
struct Heap{
	std :: priority_queue<int> A, B;
	void update(){
		while (!B.empty() && A.top() == B.top()) A.pop(), B.pop();
	}
	void push(int x){ A.push(x); }
	void pop(){ A.pop(), update(); }
	void erase(int x){ B.push(x), update(); }
	int top(){ return !A.empty() ? A.top() : -INF; }
	int top2(){
		if (A.empty()) return 0;
		int v = A.top(), res = v;
		pop(), res += top();
		return push(v), std :: max(res, 0);
	}
}hs[N], hf[N], hans;
int vis[N], sz[N], rt, fa[N];
void getrt(int Sz, int u, int fa = 0){
	bool flag = 1;
	sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa && !vis[v])
			getrt(Sz, v, u), flag &= sz[v] <= (Sz >> 1), sz[u] += sz[v];
	if (flag && Sz - sz[u] <= (Sz >> 1)) rt = u;
}
void dfs(int u, int fa = 0){
	sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa && !vis[v]) dfs(v, u), sz[u] += sz[v];
}
void solve(int Sz, int u, int lst){
	getrt(Sz, u), u = rt;
	fa[u] = lst, vis[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if (!vis[v = to[i]]) dfs(v, u);
	for (register int i = hd[u], v; i; i = pr[i])
		if (!vis[v = to[i]]) solve(sz[v], v, u);
}
void to_white(int u){
	hans.erase(hs[u].top2());
	hs[u].push(0);
	hans.push(hs[u].top2());
	for (register int v = u; fa[v]; v = fa[v]){
		hans.erase(hs[fa[v]].top2());
		hs[fa[v]].erase(hf[v].top());
		hf[v].push(dist(u, fa[v]));
		hs[fa[v]].push(hf[v].top());
		hans.push(hs[fa[v]].top2());
	}
}
void to_black(int u){
	hans.erase(hs[u].top2());
	hs[u].erase(0);
	hans.push(hs[u].top2());
	for (register int v = u; fa[v]; v = fa[v]){
		hans.erase(hs[fa[v]].top2());
		hs[fa[v]].erase(hf[v].top());
		hf[v].erase(dist(u, fa[v]));
		hs[fa[v]].push(hf[v].top());
		hans.push(hs[fa[v]].top2());
	}
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	init();
	solve(n, 1, 0);
	for (register int i = 1; i <= n; ++i)
		for (register int u = i; fa[u]; u = fa[u])
			hf[u].push(dist(i, fa[u]));
	for (register int i = 1; i <= n; ++i)
		if (fa[i]) hs[fa[i]].push(hf[i].top());
	for (register int i = 1; i <= n; ++i) col[i] = 0, ++cnt_white, hs[i].push(0);
	for (register int i = 1; i <= n; ++i) hans.push(hs[i].top2());
	q = read();
	while (q--){
		char opt = readc();
		if (opt == 'A'){
			if (cnt_white == 0) print_str("They have disappeared.");
			else if (cnt_white == 1) print(0);
			else print(hans.top());
		}
		else{
			int x = read();
			if (col[x] == 0) to_black(x), --cnt_white;
			else to_white(x), ++cnt_white;
			col[x] ^= 1;
		}
	}
}