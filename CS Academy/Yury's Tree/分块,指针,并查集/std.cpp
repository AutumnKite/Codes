#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
using std :: vector;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
struct pa{ // 手写 pair
	int fr, sc;
	pa(int x = 0, int y = 0){
		fr = x, sc = y;
	}
};
int n, q, bl;
long long a[N], ans[N]; // a 点权, ans 答案
vector<pa> to[N]; // 边表
int fa[N], idx, be[N], ed[N]; // 父亲, dfs 序
void dfs(int u){ // 求 fa, dfs 序
	be[u] = ++idx;
	for (auto i : to[u]) if (i.fr != fa[u]) fa[i.fr] = u, dfs(i.fr);
	ed[u] = idx;
}
int in(int v, int u){ // v 是否在 u 的子树内
	return be[u] <= be[v] && be[v] <= ed[u];
}
struct mq{ // 操作
	int opt, u, val, chg;
}Q[N];
vector<mq> M; // 当前块的所有修改
vector<pa> mod[N], add[N]; // mod 节点 i 的所有修改, add 节点 i 的祖先的所有修改, mod <- mod + add
int mn[N]; // i 到离 i 最近的祖先之间的边权 min
void get_mn(int u, int s = 100001){
	if (mod[u].size()) mn[u] = s, s = 100001;
	for (auto i : to[u]) if (i.fr != fa[u]) get_mn(i.fr, std :: min(s, i.sc));
}
bool cmpbeu(mq a, mq b){
	return be[a.u] < be[b.u];
}
int sta[N], top, last;
void get_gf_mod(){ // 将祖先的修改下放
	get_mn(1), std :: sort(M.begin(), M.end(), cmpbeu), top = last = 0;
	for (auto i : M){
		int u = i.u;
		if (u == last) continue;
		while (top && !in(u, sta[top])) --top;
		int s = mn[u];
		for (register int j = top; j; --j){
			for (auto k : mod[sta[j]]) if (s >= k.fr) add[u].push_back(k);
			s = std :: min(s, mn[sta[j]]);
		}
		sta[++top] = u, last = u;
	}
	for (register int i = 1; i <= n; ++i){
		for (auto j : add[i]) mod[i].push_back(j);
		add[i].clear();
	}
}
vector<pa> Mn; // update 时当前子树中的所有点, 按到根的距离大->小排序
void get_Mn(int u, int s = 100001){
	Mn.push_back(pa(s, u));
	for (auto i : to[u]) if (i.fr != fa[u] && mod[i.fr].empty()) get_Mn(i.fr, std :: min(s, i.sc));
}
pa b[N];
int cnt[260];
bool cmpfr(pa a, pa b){
	return a.fr > b.fr;
}
void Sort(vector<pa> &a){
	int n = a.size();
	if (n <= 300) return std :: sort(a.begin(), a.end(), cmpfr), void(0);
	for (register int d = 0; d < 17; d += 8){
		for (register int i = 0; i < n; ++i) b[i] = a[i], ++cnt[a[i].fr >> d & 255];
		for (register int i = 254; ~i; --i) cnt[i] += cnt[i + 1];
		for (register int i = n - 1; ~i; --i) a[--cnt[b[i].fr >> d & 255]] = b[i];
		for (register int i = 0; i < 256; ++i) cnt[i] = 0;
	}
}
vector<long long> ads; // update 时当前子树中的点要加的权值
void update(){ // 当前块的所有修改 O(n) update
	for (register int i = 1; i <= n; ++i) mod[i].clear();
	for (auto i : M) mod[i.u].push_back(pa(i.val, i.chg));
	get_gf_mod(), M.clear();
	for (register int i = 1; i <= n; ++i)
		if (mod[i].size()){
			Mn.clear(), get_Mn(i);
			Sort(Mn), Sort(mod[i]);
			int l = -1, sz = Mn.size();
			ads.resize(sz);
			for (auto r : mod[i]){
				while (l < sz - 1 && Mn[l + 1].fr >= r.fr) ++l;
				if (l >= 0) ads[l] += r.sc;
			}
			for (register int j = sz - 2; ~j; --j) ads[j] += ads[j + 1];
			for (register int j = 0; j < sz; ++j) a[Mn[j].sc] += ads[j], ads[j] = 0;
		}
}
struct DSU{
	int fa[N], dep[N];
	void init(){
		for (register int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x){
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}
	void merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (dep[x] < dep[y]) std :: swap(x, y);
		fa[y] = x, dep[x] = std :: max(dep[x], dep[y] + 1);
	}
	bool insame(int x, int y){
		return find(x) == find(y);
	}
}D;
struct Edge{
	int u, v, w;
	bool operator < (const Edge &res) const {
		return w > res.w;
	}
}E[N]; // 边 (按边权从大到小)
vector<int> af[N]; // 块中第 i 个修改后面可能有影响的询问编号
vector<mq> Mod; // 所有修改 (按 val 从大到小)
bool cmpval(mq a, mq b){
	return a.val > b.val;
}
int main(){
	n = read(), q = read(), bl = 2500;
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), E[i] = (Edge){u, v, w},
		to[u].push_back(pa(v, w)), to[v].push_back(pa(u, w));
	dfs(1);
	for (register int i = 1, pos = 1; i <= q; ++i){
		Q[i].opt = read();
		if (Q[i].opt == 1){
			Q[i].opt = 0, Q[i].u = read(), ans[i] = a[Q[i].u];
			for (register int j = pos; j < i; ++j)
				if (Q[j].opt && in(Q[i].u, Q[j].u)) af[j].push_back(i);
		}
		else{
			Q[i].opt = i, Q[i].chg = read(), Q[i].val = read(), Q[i].u = read();
			M.push_back(Q[i]), Mod.push_back(Q[i]);
		}
		if (i % bl == 0) update(), pos += bl;
	}
	std :: sort(E + 1, E + n), std :: sort(Mod.begin(), Mod.end(), cmpval);
	D.init();
	register int l = 0;
	for (auto r : Mod){
		while (l < n - 1 && E[l + 1].w >= r.val) ++l, D.merge(E[l].u, E[l].v);
		for (auto i : af[r.opt]) if (D.insame(Q[i].u, r.u)) ans[i] += r.chg;
	}
	for (register int i = 1; i <= q; ++i)
		if (!Q[i].opt) printf("%lld\n", ans[i]);
}

