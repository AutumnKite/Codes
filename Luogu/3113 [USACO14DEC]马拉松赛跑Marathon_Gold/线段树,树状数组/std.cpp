#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, q;
struct node{
	int x, y;
}a[N];
long long sum[N];
int abs(int x){ return x >= 0 ? x : -x; }
int dis(node a, node b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}
int calc(int x){
	return dis(a[x - 1], a[x]) + dis(a[x], a[x + 1]) - dis(a[x - 1], a[x + 1]);
}
struct Segment_Tree{
	int mx[N << 2];
	void modify(int u, int l, int r, int x, int y){
		if (l == r) return mx[u] = y, void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, y);
		else modify(u << 1 | 1, md + 1, r, x, y);
		mx[u] = std :: max(mx[u << 1], mx[u << 1 | 1]);
	}
	int query(int u, int l, int r, int L, int R){
		if (L > R) return 0;
		if (L <= l && r <= R) return mx[u];
		int md = (l + r) >> 1;
		if (R <= md) return query(u << 1, l, md, L, R);
		else if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		else return std :: max(query(u << 1, l, md, L, R), query(u << 1 | 1, md + 1, r, L, R));
	}
}T;
struct BIT{
	long long c[N];
	void add(int x, int y){
		for (; x <= n; x += x & -x) c[x] += y;
	}
	long long query(int l, int r){
		long long s = 0;
		for (; r; r -= r & -r) s += c[r];
		for (--l; l; l -= l & -l) s -= c[l];
		return s;
	}
}B;
int main(){
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i) a[i].x = read(), a[i].y = read();
	for (register int i = 2; i <= n; ++i) B.add(i, dis(a[i - 1], a[i]));
	for (register int i = 2; i < n; ++i) T.modify(1, 1, n, i, calc(i));
	while (q--){
		char opt[5];
		scanf("%s", opt);
		if (*opt == 'U'){
			int k = read();
			B.add(k, -dis(a[k - 1], a[k]));
			if (k < n) B.add(k + 1, -dis(a[k], a[k + 1]));
			a[k].x = read(), a[k].y = read();
			B.add(k, dis(a[k - 1], a[k]));
			if (k < n) B.add(k + 1, dis(a[k], a[k + 1]));
			if (k > 2) T.modify(1, 1, n, k - 1, calc(k - 1));
			if (k < n - 1) T.modify(1, 1, n, k + 1, calc(k + 1));
			if (2 <= k && k <= n - 1) T.modify(1, 1, n, k, calc(k));
		}
		else{
			int l = read(), r = read();
			printf("%lld\n", B.query(l + 1, r) - T.query(1, 1, n, l + 1, r - 1));
		}
	}
}