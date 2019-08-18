#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x; 
}
#define N 1000005
#define P 1000000000000000000ll
int n, a[N], m, b[N];
long long c[N];
long long ans1, ans2;
void add(int x, long long y){
	for (; x <= m; x += x & -x) c[x] += y;
}
long long query(int x){
	long long s = 0;
	for (; x; x -= x & -x) s += c[x];
	return s;
}
int calc(long long x){
	int s = 18;
	while (x) --s, x /= 10;
	return s;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = b[i] = read();
	std :: sort(b + 1, b + 1 + n);
	m = std :: unique(b + 1, b + 1 + n) - b - 1;
	for (register int i = 1; i <= n; ++i)
		a[i] = std :: lower_bound(b + 1, b + 1 + m, a[i]) - b;
	for (register int i = n; i; --i){
		long long x = i * query(a[i] - 1);
		ans2 += x;
		if (ans2 > P) ans1 += ans2 / P, ans2 %= P;
		add(a[i], n - i + 1);
	}
	if (!ans1) printf("%lld", ans2);
	else{
		printf("%lld", ans1);
		for (register int i = calc(ans2); i; --i) putchar('0');
		printf("%lld", ans2);
	}
}
