#include <cstdio>
#include <cctype>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, x, y;
long long ans;
int abs(int a){
	return a > 0 ? a : -a;
}
int main(){
	n = read(), y = read();
	for (register int i = 2; i <= n; ++i) x = read(), ans += abs(x - y), y = x;
	printf("%lld\n", ans);
}