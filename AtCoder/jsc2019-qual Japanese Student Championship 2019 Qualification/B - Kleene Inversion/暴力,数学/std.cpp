#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define P 1000000007
int n, k, a[2005], s1, s2;
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i)
		for (register int j = i + 1; j <= n; ++j)
			if (a[i] > a[j]) ++s1;
	s1 = 1ll * s1 * k % P;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			if (a[i] > a[j]) ++s2;
	s2 = (1ll * k * (k - 1) >> 1) % P * s2 % P;
	printf("%d\n", (s1 + s2) % P);
}
