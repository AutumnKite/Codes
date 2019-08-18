#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
#define INF 1000000000
int n, m;
struct node{
	int v, l, r, id, ans;
}a[N];
bool cmp1(node a, node b){ return a.v < b.v; }
bool cmp2(node a, node b){ return a.r < b.r; }
bool cmp3(node a, node b){ return a.id < b.id; }
int c[N];
void Add(int x, int y){
	for (; x <= 100000; x += x & -x) c[x] = std :: max(c[x], y);
}
int Query(int x){
	int ans = 0;
	for (; x; x -= x & -x) ans = std :: max(ans, c[x]);
	return ans;
}
void Del(int x){
	for (; x <= 100000; x += x & -x) c[x] = 0;
}
void cdq(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	std :: sort(a + l, a + mid + 1, cmp1), std :: sort(a + mid + 1, a + r + 1, cmp2);
	int i = l, j = mid + 1;
	for (; i <= mid && j <= r; ++j){
		for (; a[i].r <= a[j].v && i <= mid; ++i) Add(a[i].v, a[i].ans);
		a[j].ans = std :: max(a[j].ans, Query(a[j].l) + 1);
	}
	for (; j <= r; ++j) a[j].ans = std :: max(a[j].ans, Query(a[j].l) + 1);
	for (i = l; i <= mid; ++i) Del(i);
	std :: sort(a + l, a + r + 1, cmp3);
	cdq(mid + 1, r);
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i].l = a[i].r = a[i].v = read();
	for (register int i = 1; i <= m; ++i){
		int x = read(), y = read();
		a[x].l = std :: min(a[x].l, y), a[x].r = std :: max(a[x].r, y);
	}
	cdq(1, n);
	int ans = 0;
	for (register int i = 1; i <= n; ++i) ans = std :: max(ans, a[i].ans);
	printf("%d", ans);
}