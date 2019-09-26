#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
#define INF 0x3f3f3f3f3f3f3f3fll
int n;
struct node{
	long long x, y;
}a[N];
long long x[N], y[N], sx[N], sy[N], ans;
long long abs(long long x){
	return x >= 0 ? x : -x;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i){
		long long _x = read(), _y = read();
		x[i] = a[i].x = _x - _y, y[i] = a[i].y = _x + _y;
	}
	std :: sort(x + 1, x + 1 + n), std :: sort(y + 1, y + 1 + n);
	for (register int i = 1; i <= n; ++i)
		sx[i] = sx[i - 1] + x[i], sy[i] = sy[i - 1] + y[i];
	ans = INF;
	for (register int i = 1; i <= n; ++i){
		int px = std :: lower_bound(x + 1, x + 1 + n, a[i].x) - x - 1;
		int py = std :: lower_bound(y + 1, y + 1 + n, a[i].y) - y - 1;
		long long sumx = a[i].x * px - sx[px] + sx[n] - sx[px] - a[i].x * (n - px);
		long long sumy = a[i].y * py - sy[py] + sy[n] - sy[py] - a[i].y * (n - py);
		ans = std :: min(ans, sumx + sumy);
	}
	printf("%lld\n", ans >> 1);
}