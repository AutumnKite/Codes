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
#define N 600005
int n, m, a[N], rt[N];
struct trie{
	int cnt, son[N * 24][2], mx[N * 24];
	int insert(int _u, int x, int id){
		int u = ++cnt, rt = u;
		for (register int i = 23; ~i; --i){
			int w = x >> i & 1;
			mx[u] = std :: max(mx[_u], id), son[u][w] = ++cnt, son[u][w ^ 1] = son[_u][w ^ 1];
			u = son[u][w], _u = son[_u][w];
		}
		mx[u] = std :: max(mx[_u], id);
		return rt;
	}
	int query(int u, int x, int id){
		int res = 0;
		for (register int i = 23; ~i; --i){
			int w = x >> i & 1;
			if (mx[son[u][w ^ 1]] >= id) res = res << 1 | (w ^ 1), u = son[u][w ^ 1];
			else res = res << 1 | w, u = son[u][w];
		}
		return res ^ x;
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = n - 1; i; --i) a[i] ^= a[i + 1];
	for (register int i = 1; i <= n; ++i) rt[i] = T.insert(rt[i - 1], a[i], i);
	int val = 0;
	while (m--){
		char opt[5];
		int l, r, x;
		scanf("%s", opt);
		if (*opt == 'A') x = read(), a[++n] = val, val ^= x, rt[n] = T.insert(rt[n - 1], a[n], n);
		else l = read(), r = read(), x = read(), printf("%d\n", T.query(rt[r], val ^ x, l));
	}
}