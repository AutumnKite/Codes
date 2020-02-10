#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
char pbuf[1 << 23], *pp = pbuf;
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(long long x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 5005;
int n, m, k;
long long a[N][N], s[N];
long long abs(long long a){ return a > 0 ? a : -a; }
int main(){
	n = read(), m = read(), k = read();
	for (register int i = 1, u, v; i <= m; ++i)
		u = read(), v = read(), a[u][v] = read();
	long long ans = 0;
	for (register int i = 1; i <= n; ++i){
		long long sum = 0;
		for (register int j = 1; j <= n; ++j){
			if (i > k) s[j] -= a[i - k][j];
			sum += s[j] - (j > k ? s[j - k] : 0);
			long long tmp = sum + a[i][j];
			if ((i > n - k + 1 || j > n - k + 1) && tmp) return print(-1), 0;
			ans += abs(-tmp), a[i][j] = -tmp, s[j] += a[i][j], sum += a[i][j];
		}
	}
	print(ans);
}