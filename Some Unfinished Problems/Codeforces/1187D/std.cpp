#include <cstdio>
#include <algorithm>
#define N 300005
int T, n, ca[N], cb[N];
struct Fenwick_Tree{
	int c[N];
	void add(int x){
		for (; x <= n; x += x & -x) ++c[x];
	}
	int query(int x){
		int sum = 0;
		for (; x; x -= x & -x) sum += c[x];
		return sum;
	}
}Ta, Tb;
struct node{
	int x, y;
	bool operator < (const node &res) const {
		return x < res.x || (x == res.x && y < res.y);
	}
}a[N], b[N];
bool check(){
	for (register int i = 1; i <= n; ++i) if (ca[i] != cb[i]) return 0;
	for (register int i = 1; i <= n; ++i) Ta.c[i] = Tb.c[i] = 0;
	for (register int i = 1; i <= n; ++i){
		if (Ta.query(a[i].y) > Tb.query(b[i].y)) return 0;
		Ta.add(a[i].y), Tb.add(b[i].y);
	}
	return 1;
}
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n);
		for (register int i = 1; i <= n; ++i) ca[i] = cb[i] = 0;
		for (register int i = 1, x; i <= n; ++i)
			scanf("%d", &x), ++ca[x], a[i] = (node){x, i};
		for (register int i = 1, x; i <= n; ++i)
			scanf("%d", &x), ++cb[x], b[i] = (node){x, i};
		std :: sort(a + 1, a + 1 + n), std :: sort(b + 1, b + 1 + n);
		if (!check()) printf("NO\n"); else printf("YES\n");
	}
}