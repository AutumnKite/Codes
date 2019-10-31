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
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 200005;
char s[5];
int n, q, a[N], c[N];
namespace segt{
	struct node{
		int c, l, r, s;
		void init(int v){
			s = 0;
			if (v) c = l = r = 1;
			else c = l = r = 0;
		}
	}a[N << 2];
	node operator + (const node &a, const node &b){
		node c;
		c.c = a.c + b.c, c.l = a.l, c.r = b.r;
		c.s = a.s + b.s;
		if (a.c && b.c && (!a.r || !b.l)) ++c.s;
		return c;
	}
	void modify(int u, int l, int r, int x, int v){
		if (l == r) return a[u].init(v), void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, v);
		else modify(u << 1 | 1, md + 1, r, x, v);
		a[u] = a[u << 1] + a[u << 1 | 1];
	}
	node query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return a[u];
		int md = (l + r) >> 1;
		if (R <= md) return query(u << 1, l, md, L, R);
		else if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		else return query(u << 1, l, md, L, R) + query(u << 1 | 1, md + 1, r, L, R);
	}
}
int calc(int i){ return c[i] ? a[i] * a[i - 1] % 10 : (a[i] + a[i - 1]) % 10; }
int main(){
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i){
		a[i] = read(), scanf("%s", s), c[i] = s[0] == '*';
		a[n + i] = a[i], c[n + i] = c[i];
	}
	for (register int i = 2; i <= (n << 1); ++i)
		segt :: modify(1, 1, n << 1, i, calc(i));
	while (q--){
		int op = read(), x = read() + 1;
		if (op == 1){
			a[x] = read(), scanf("%s", s), c[x] = s[0] == '*';
			a[n + x] = a[x], c[n + x] = c[x];
			if (x > 1) segt :: modify(1, 1, n << 1, x, calc(x));
			segt :: modify(1, 1, n << 1, x + 1, calc(x + 1));
			segt :: modify(1, 1, n << 1, n + x, calc(n + x));
			if (x < n) segt :: modify(1, 1, n << 1, n + x + 1, calc(n + x + 1));
		}
		else{
			if (!a[x] && segt :: query(1, 1, n << 1, x + 1, n + x - 1).s == 0){ puts("0"); continue; }
			segt :: modify(1, 1, n << 1, x, a[x]);
			segt :: modify(1, 1, n << 1, n + x, a[x]);
			int l = 0, r = n >> 1, md, ans = -2;
			while (l <= r)
				if (md = (l + r) >> 1, segt :: query(1, 1, n << 1, x + md, n + x - md).s) ans = md, l = md + 1;
				else r = md - 1;
			++ans;
			print(ans);
			if (x > 1) segt :: modify(1, 1, n << 1, x, calc(x));
			segt :: modify(1, 1, n << 1, n + x, calc(n + x));
		}
	}
}
