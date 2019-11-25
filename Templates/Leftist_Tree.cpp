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
const int N = 300005;
int n, m;
struct Leftist_Tree{
	int cnt, fa[N], ls[N], rs[N], dis[N], val[N];
	Leftist_Tree(){ cnt = 0, dis[0] = -1; }
	int new_node(int v){
		int u = ++cnt;
		return fa[u] = u, ls[u] = rs[u] = 0, dis[u] = 0, val[u] = v, u;
	}
	int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
	int merge(int x, int y){
		if (!x || !y) return x | y;
		if (val[x] > val[y] || (val[x] == val[y] && x > y)) std :: swap(x, y);
		rs[x] = merge(rs[x], y);
		if (dis[ls[x]] < dis[rs[x]]) std :: swap(ls[x], rs[x]);
		return dis[x] = dis[rs[x]] + 1, fa[ls[x]] = fa[rs[x]] = fa[x] = x;
	}
	void pop(int x){
		fa[ls[x]] = ls[x], fa[rs[x]] = rs[x], fa[x] = merge(ls[x], rs[x]), val[x] = -1;
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) T.new_node(read());
	while (m--){
		int op = read();
		if (op == 1){
			int x = read(), y = read();
			if (~T.val[x] && ~T.val[y])
				x = T.find(x), y = T.find(y), x != y ? T.merge(x, y) : 0;
		}
		else{
			int x = read();
			if (~T.val[x]) x = T.find(x), print(T.val[x]), T.pop(x);
			else print(-1);
		}
	}
}