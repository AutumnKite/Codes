#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 105;
int n, m, p[N * 3], f[N][N * 3];
struct node{
	int x, l, r;
	bool operator < (const node &rhs) const { return x < rhs.x; }
}a[N];
void chkmx(int &a, int b){ b > a ? a = b : 0; }
int main(){
	n = read();
	for (register int i = 1, t; i <= n; ++i){
		a[i].x = read(), t = read(), a[i].l = a[i].x - t, a[i].r = a[i].x + t;
		p[++m] = a[i].x, p[++m] = a[i].l, p[++m] = a[i].r;
	}
	std :: sort(p + 1, p + 1 + m);
	m = std :: unique(p + 1, p + 1 + m) - p - 1;
	for (register int i = 1; i <= n; ++i){
		a[i].x = std :: lower_bound(p + 1, p + 1 + m, a[i].x) - p;
		a[i].l = std :: lower_bound(p + 1, p + 1 + m, a[i].l) - p;
		a[i].r = std :: lower_bound(p + 1, p + 1 + m, a[i].r) - p;
	}
	f[n][a[n].l] = f[n][a[n].x] = p[a[n].r] - p[a[n].x];
	for (register int i = n; i > 1; --i)
		for (register int j = 0; j <= a[i].x; ++j){
			int mn = 1e9;
			for (register int k = i - 1; k; --k){
				int l = std :: min(a[k].x, mn);
				if (a[i - 1].x <= a[k].r)
					chkmx(f[k][l], f[i][j] + p[std :: min(a[k].r, j)] - p[l]);
				mn = std :: min(mn, a[k].l);
			}
			mn = 1e9;
			for (register int k = i - 1; k; --k)
				if (a[k].x > a[i - 1].l) mn = std :: min(mn, a[k].l);
			chkmx(f[i - 1][mn], f[i][j] + p[std :: min(a[i - 1].r, j)])
		}
	int ans = 0;
	for (register int i = 1; i <= n; ++i) ans = std :: max
}