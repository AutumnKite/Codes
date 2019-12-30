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
const int N = 100005;
int n, q;
struct BIT{
	int c[N];
	void add(int x, int v){
		for (; x <= n; x += x & -x) c[x] += v;
	}
	int query(int x){
		int s = 0;
		for (; x; x ^= x & -x) s += c[x];
		return s;
	}
}Tl, Tr;
int main(){
	n = read(), q = read();
	int m = 0;
	while (q--){
		int op = read(), l = read(), r = read();
		if (op == 1) Tl.add(l, 1), Tr.add(r, 1), ++m;
		else print(m - (Tr.query(l - 1) + m - Tl.query(r)));
	}
}