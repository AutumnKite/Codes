#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
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
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 1000005;
int n, k, b[N];
long long a[N];
std::vector<int> ans;
void add(int l, int r){
	if (r > k) r = k + 1;
	++b[l], --b[r];
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = a[i - 1] + read();
	k = read();
	for (register int i = 1; i <= n; ++i){
		if (a[i] > k) break;
		int j = std::lower_bound(a + 1, a + 1 + n, 2 * a[i]) - a;
		add(a[i], a[j] - a[i]);
	}
	for (register int i = 1; i <= k; ++i) b[i] += b[i - 1];
	for (register int i = 1; i <= k; ++i) if (b[i]) ans.push_back(i);
	print(ans.size());
	for (register int i = 0; i < (int)ans.size(); ++i) print(ans[i], ' ');
	putchar('\n');
}