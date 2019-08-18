#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, x, s1, s2;
int main(){
	int T = read();
	while (T--){
		n = read(), s1 = 0, s2 = 0;
		for (register int i = 1; i <= n; ++i)
			x = read(), s1 += x < 0, s2 += x > 0;
		printf("%d ", std :: max(s1, s2));
		if (s1 && s2) printf("%d\n", std :: min(s1, s2));
		else printf("%d\n", std :: max(s1, s2));
	}
}
