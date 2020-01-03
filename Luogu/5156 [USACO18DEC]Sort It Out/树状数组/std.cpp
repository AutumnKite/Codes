#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
long long read(){
	register long long x = 0;
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
const long long INF = 0x3f3f3f3f3f3f3f3fll;
int n, a[N], vis[N];
long long k;
struct node{
	int len;
	long long tot;
	node(){ len = tot = 0; }
	node(int _len, long long _tot){ len = _len, tot = _tot; }
	void upd(const node &rhs){
		if (rhs.len > len) len = rhs.len, tot = rhs.tot;
		else if (rhs.len == len) tot = std::min(tot + rhs.tot, INF);
	}
}c[N], f[N];
std::vector<int> pos[N];
void add(int x, node v){
	for (; x; x ^= x & -x) c[x].upd(v);
}
node query(int x){
	node s;
	for (; x <= n + 1; x += x & -x) s.upd(c[x]);
	return s;
}
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	f[n + 1] = node(0, 1), add(n + 1, f[n + 1]);
	for (register int i = n; i; --i)
		f[i] = query(a[i] + 1), ++f[i].len, add(a[i], f[i]);
	for (register int i = 1; i <= n; ++i) pos[f[i].len].push_back(i);
	int m = query(1).len;
	print(n - m);
	for (register int i = m, lst = 0; i; --i){
		int t = 0;
		for (int j : pos[i])
			if (j > lst){
				if (k > f[j].tot) k -= f[j].tot;
				else { t = j; break; }
			}
		vis[a[t]] = 1, lst = t;
	}
	for (register int i = 1; i <= n; ++i)
		if (!vis[i]) print(i);
}