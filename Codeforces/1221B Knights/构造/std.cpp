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
int n;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n || (putchar('\n'), 0); ++j)
			if ((i & 1) == (j & 1)) putchar('W'); else putchar('B');
}