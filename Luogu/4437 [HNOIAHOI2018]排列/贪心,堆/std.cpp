#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 500005
int n, fa[N], Fa[N], sz[N];
long long val[N], ans;
int find(int x){
	return Fa[x] == x ? x : (Fa[x] = find(Fa[x]));
}
struct node{
	int id, sz;
	long long w;
	bool operator < (const node &b) const {
		return w * b.sz > b.w * sz;
	}
};
struct Heap{
	node h[N << 2];
	int sz;
	void clear(){ sz = 0; }
	bool empty(){ return !sz; }
	void push(node a){ h[++sz] = a, std :: push_heap(h + 1, h + 1 + sz); }
	node pop(){ return std :: pop_heap(h + 1, h + 1 + sz), h[sz--]; }
	node top(){ return h[1]; }
}H;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) Fa[i] = i;
	for (register int i = 1, x, y; i <= n; ++i){
		fa[i] = read(), x = find(i), y = find(fa[i]);
		if (x == y) return printf("-1"), 0;
		Fa[x] = y;
	}
	for (register int i = 1; i <= n; ++i)
		val[i] = read(), Fa[i] = i, sz[i] = 1, H.push((node){i, 1, val[i]});
	Fa[0] = 0, sz[0] = 1;
	while (!H.empty()){
		node x = H.pop();
		int fx = find(x.id), fy = find(fa[x.id]);
		if (sz[fx] != x.sz) continue;
		ans += val[fx] * sz[fy];
		Fa[fx] = fy, sz[fy] += sz[fx], val[fy] += val[fx];
		if (fy) H.push((node){fy, sz[fy], val[fy]});
	}
	printf("%lld", ans);
}