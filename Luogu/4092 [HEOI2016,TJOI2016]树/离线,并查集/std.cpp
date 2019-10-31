#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, int ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 100005;
int n, q, fa[N], cnt[N], k, ans[N];
struct node{
	int op, x;
}Q[N];
char opt[5];
namespace dsu{
	int fa[N];
	void init(int n){
		for (register int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
	void merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return;
		fa[y] = x;
	}
}
int main(){
	n = read(), q = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), fa[v] = u;
	for (register int i = 1; i <= q; ++i){
		scanf("%s", opt), Q[i].x = read();
		if (opt[0] == 'C') Q[i].op = 1, ++cnt[Q[i].x];
		else Q[i].op = 2;
	}
	dsu :: init(n), ++cnt[1];
	for (register int i = 2; i <= n; ++i)
		if (!cnt[i]) dsu :: merge(fa[i], i);
	for (register int i = q; i; --i)
		if (Q[i].op == 1) if (!(--cnt[Q[i].x])) dsu :: merge(fa[Q[i].x], Q[i].x); else continue;
		else ans[++k] = dsu :: find(Q[i].x);
	while (k) print(ans[k--]);
}