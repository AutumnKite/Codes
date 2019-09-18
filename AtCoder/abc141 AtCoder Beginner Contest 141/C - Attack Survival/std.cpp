#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, k, q, a[100005];
int main(){
	n = read(), k = read(), q = read();
	for (register int i = 1; i <= n; ++i) a[i] = k - q;
	for (register int i = 1; i <= q; ++i) ++a[read()];
	for (register int i = 1; i <= n; ++i) if (a[i] > 0) puts("Yes"); else puts("No");
}