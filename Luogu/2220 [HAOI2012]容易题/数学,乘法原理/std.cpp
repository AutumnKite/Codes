#include <cstdio>
#include <algorithm>
#define P 1000000007
int n, m, k, cnt, ans, s;
struct node{
	int x, y;
	bool operator < (const node &res) const {
		return x < res.x || (x == res.x && y < res.y);
	}
}a[100005];
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int sub(int x, int y){ return (x -= y) < 0 ? x + P : x; }
int main(){
	scanf("%d%d%d", &n, &m, &k), s = (1ll * n * (n + 1) >> 1) % P, ans = 1;
	for (register int i = 1, x, y; i <= k; ++i) scanf("%d%d", &a[i].x, &a[i].y);
	std :: sort(a + 1, a + 1 + k);
	for (register int i = 1, j = i; i <= k; i = j){
		int w = sub(s, a[i].y);
		while (a[j].x == a[i].x) ++j;
		for (register int t = i + 1; t < j; ++t)
			if (a[t].y != a[t - 1].y) w = sub(w, a[t].y);
		ans = 1ll * ans * w % P, ++cnt;
	}
	ans = 1ll * ans * qpow(s, m - cnt) % P;
	printf("%d\n", ans);
}