#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 300005;
int n, m, cnt;
struct node{
	int l, r, len;
	bool operator < (const node &rhs) const { return len < rhs.len; }
}a[N];
struct BIT{
	int c[N];
	void add(int x, int v){
		for (; x <= m; x += x & -x) c[x] += v;
	}
	int query(int x){
		int s = 0;
		for (; x; x ^= x & -x) s += c[x];
		return s;
	}
}Tl, Tr;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		a[i].l = read(), a[i].r = read(), a[i].len = a[i].r - a[i].l + 1;
	std::sort(a + 1, a + 1 + n);
	int k = 1;
	for (register int i = 1; i <= m; ++i){
		int s = n - k + 1;
		for (register int j = i; j <= m; j += i)
			s += Tl.query(j) - Tr.query(j - 1);
		print(s);
		while (k <= n && a[k].len == i) Tl.add(a[k].l, 1), Tr.add(a[k].r, 1), ++k;
	}
}