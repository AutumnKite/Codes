#include <cstdio>
#include <algorithm>
#define N 500005
int n, m, x;
double k[N], b[N];
char opt[15];
struct Li_Chao_Segment_Tree{
	int id[N];
	int check(int u, int v, int x){
		return k[u] * (x - 1) + b[u] <= k[v] * (x - 1) + b[v];
	}
	void Insert(int u, int l, int r, int x){
		if (check(id[u], x, l) && check(id[u], x, r)) return id[u] = x, void(0);
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (check(id[u], x, mid)) std :: swap(id[u], x);
		if (check(id[u], x, l)) Insert(u << 1, l, mid, x);
		if (check(id[u], x, r)) Insert(u << 1 | 1, mid + 1, r, x);
	}
	double Query(int u, int l, int r, int x){
		if (l == r) return k[l] * (x - 1) + b[l];
		int mid = (l + r) >> 1;
		double ans;
		if (x <= mid) ans = Query(u << 1, l, mid, x);
		else ans = Query(u << 1 | 1, mid + 1, r, x);
		return std :: max(ans, k[id[u]] * (x - 1) + b[id[u]]);
	}
}T;
int main(){
	for (scanf("%d", &m); m--; ){
		scanf("%s", opt);
		if (opt[0] == 'P') ++n, scanf("%lf%lf", b + n, k + n), T.Insert(1, 1, 50000, n);
		else scanf("%d", &x), printf("%d\n", int(T.Query(1, 1, 50000, x) / 100));
	}
}