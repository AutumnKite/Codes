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
#define N 55
int n, a[N];
double s;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	std :: sort(a + 1, a + 1 + n);
	s = a[1];
	for (register int i = 2; i <= n; ++i)
		s = (s + a[i]) / 2;
	printf("%.10lf\n", s);
}