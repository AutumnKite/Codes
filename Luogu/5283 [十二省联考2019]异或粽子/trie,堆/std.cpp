#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
unsigned int read(){
	register unsigned int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 500005
int n, m;
unsigned int a[N];
struct Trie{
	int cnt, sum[N << 5], son[N << 5][2];
	Trie(){ cnt = 1; }
	void insert(unsigned int x){
		int u = 1;
		++sum[1];
		for (register int i = 31; ~i; u = son[u][x >> i & 1], ++sum[u], --i)
			if (!son[u][x >> i & 1]) son[u][x >> i & 1] = ++cnt;
	}
	unsigned int query(unsigned int x, int k){
		int u = 1;
		unsigned int res = 0;
		for (register int i = 31; ~i; --i){
			int l = !(x >> i & 1), r = x >> i & 1;
			if (k <= sum[son[u][l]]) u = son[u][l], res = res << 1 | l;
			else k -= sum[son[u][l]], u = son[u][r], res = res << 1 | r;
		}
		return x ^ res;
	}
}T;
struct Heap{
	int sz;
	std :: pair<unsigned int, int> a[N];
	void push(std :: pair<unsigned int, int> x){ a[++sz] = x, std :: push_heap(a + 1, a + 1 + sz); }
	std :: pair<unsigned int, int> pop(){ return std :: pop_heap(a + 1, a + 1 + sz), a[sz--]; }
}H;
int cnt[N];
long long ans;
int main(){
	n = read(), m = read(), T.insert(0);
	for (register int i = 1; i <= n; ++i) a[i] = a[i - 1] ^ read(), T.insert(a[i]);
	m <<= 1;
	for (register int i = 0; i <= n; ++i)
		cnt[i] = 1, H.push(std :: make_pair(T.query(a[i], 1), i));
	for (register int i = 1; i <= m; ++i){
		std :: pair<unsigned int, int> x = H.pop();
		ans += x.first;
		++cnt[x.second], H.push(std :: make_pair(T.query(a[x.second], cnt[x.second]), x.second));
	}
	printf("%lld\n", ans >> 1);
}