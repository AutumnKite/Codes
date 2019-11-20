#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
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
const int N = 500005, INF = 0x3f3f3f3f;
int n, q, A[N], cnt;
struct node{
	int mn, pos;
	node operator + (const node &rhs) const {
		if (mn <= rhs.mn) return *this; else return rhs;
	}
}ans[N];
struct Segment_Tree{
	node a[N << 2];
	int lz[N << 2];
	void build(int u, int l, int r){
		if (l == r) return a[u] = (node){A[l], l}, void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		a[u] = a[u << 1] + a[u << 1 | 1];
	}
	void chkmx(int u, int v){
		if (v > a[u].mn) a[u].mn = lz[u] = v;
	}
	void down(int u){
		if (lz[u]) chkmx(u << 1, lz[u]), chkmx(u << 1 | 1, lz[u]), lz[u] = 0;
	}
	void modify_one(int u, int l, int r, int x, int v){
		if (l == r) return a[u].mn = v, void(0);
		int md = (l + r) >> 1;
		down(u);
		if (x <= md) modify_one(u << 1, l, md, x, v);
		else modify_one(u << 1 | 1, md + 1, r, x, v);
		a[u] = a[u << 1] + a[u << 1 | 1];
	}
	void modify(int u, int l, int r, int L, int R, int v){
		if (L <= l && r <= R) return chkmx(u, v), void(0);
		int md = (l + r) >> 1;
		down(u);
		if (L <= md) modify(u << 1, l, md, L, R, v);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, v);
		a[u] = a[u << 1] + a[u << 1 | 1];
	}
	node query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return a[u];
		int md = (l + r) >> 1;
		down(u);
		if (R <= md) return query(u << 1, l, md, L, R);
		else if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		return query(u << 1, l, md, L, R) + query(u << 1 | 1, md + 1, r, L, R);
	}
}T;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) A[i] = read();
	T.build(1, 1, n);
	q = read();
	while (q--){
		int op = read(), l = read(), r = read(), v = read(), k;
		if (op == 1) T.modify(1, 1, n, l, r, v);
		else{
			node tmp;
			k = read(), cnt = 0;
			while (cnt < k && (tmp = T.query(1, 1, n, l, r), tmp.mn < v))
				ans[++cnt] = tmp, T.modify_one(1, 1, n, tmp.pos, INF);
			for (register int i = 1; i <= cnt; ++i) T.modify_one(1, 1, n, ans[i].pos, ans[i].mn);
			if (cnt < k) print(-1);
			else for (register int i = 1; i <= k; ++i) print(ans[i].mn, " \n"[i == k]);
		}
	}
}