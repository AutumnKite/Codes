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
const int N = 100005;
int n, q;
struct node{
	int a, b;
	bool operator < (const node &rhs) const { return 1ll * a * rhs.b < 1ll * rhs.a * b; }
};
struct Segment_Tree{
	node mx[N << 2];
	int s[N << 2];
	void build(int u, int l, int r){
		if (l == r) return mx[u] = (node){0, l}, void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		mx[u] = std::max(mx[u << 1], mx[u << 1 | 1]);
	}
	int query(int u, int l, int r, node pmx){
		if (l == r) return pmx < mx[u];
		int md = (l + r) >> 1;
		if (pmx < mx[u << 1]) return query(u << 1, l, md, pmx) + s[u << 1 | 1];
		else return query(u << 1 | 1, md + 1, r, pmx);
	}
	void modify(int u, int l, int r, int x, int y){
		if (l == r) return mx[u].a = y, void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, y);
		else modify(u << 1 | 1, md + 1, r, x, y);
		s[u << 1 | 1] = query(u << 1 | 1, md + 1, r, mx[u << 1]);
		mx[u] = std::max(mx[u << 1], mx[u << 1 | 1]);
	}
}T;
int main(){
	n = read(), q = read();
	T.build(1, 1, n);
	while (q--){
		int x = read(), y = read();
		T.modify(1, 1, n, x, y);
		print(T.query(1, 1, n, (node){0, 1}));
	}
}