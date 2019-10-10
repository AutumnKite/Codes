#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
int n, m;
char s[60];
long long a[60];
void insert(long long x){
	for (register int i = m - 1; ~i; --i)
		if (x >> i & 1) if (a[i]) x ^= a[i]; else return a[i] = x, void(0);
}
int main(){
	m = read(), n = read();
	for (register int i = 1; i <= n; ++i){
		scanf("%s", s + 1);
		long long x = 0;
		for (register int j = 1; j <= m; ++j) x = x << 1 | (s[j] == 'O');
		insert(x);
	}
	int s = 0;
	for (register int i = 0; i < m; ++i)
		if (a[i]) ++s;
	printf("%lld\n", (1ll << s) % 2008);
}