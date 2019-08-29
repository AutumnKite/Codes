#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, h, w, fa[200005], g[200005];
long long ans;
struct node{
	int r, c, v;
	bool operator < (const node &rhs) const {
		return v > rhs.v;
	}
}a[100005];
int find(int x){
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}
bool merge(int x, int y){
	x = find(x), y = find(y);
	if (x == y) if (g[x]) return 0; else return g[x] = 1, 1;
	if (g[x] && g[y]) return 0;
	return fa[y] = x, g[x] |= g[y], 1;
}
int main(){
	n = read(), h = read(), w = read();
	for (register int i = 1; i <= n; ++i)
		a[i].r = read(), a[i].c = read(), a[i].v = read();
	std :: sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= h + w; ++i) fa[i] = i, g[i] = 0;
	for (register int i = 1; i <= n; ++i)
		if (merge(a[i].r, a[i].c + h)) ans += a[i].v;
	printf("%lld\n", ans);
}
