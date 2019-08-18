#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	int x = 0;
	char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n;
long long w, a[100005], b[100005], ans = -1000000000000000000ll;
void work(int n, long long *a, long long *b){
	register int y = 1;
	for (register int x = 1; x <= n; ++x){
		while (b[y] < a[x] && y <= n) ++y;
		if (y == n + 1) break;
		ans = std :: max(ans, a[x] - w * (x + y));
	}
}
int main(){
	freopen("candy.in", "r", stdin);
	freopen("candy.out", "w", stdout);
	n = read(), w = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i) b[i] = read();
	std :: reverse(a + 1, a + 1 + n), std :: reverse(b + 1, b + 1 + n);
	for (register int i = 1; i <= n; ++i) a[i] += a[i - 1], b[i] += b[i - 1];
	work(n, a, b), work(n, b, a);
	printf("%lld", ans);
}