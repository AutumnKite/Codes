#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
int n, q, fa[N];
long long a[N], c[N];
int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
void add(int x, long long y){
	for (; x <= n; x += x & -x) c[x] += y;
}
long long query(int x){
	long long s = 0;
	for (; x; x ^= x & -x) s += c[x];
	return s;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), add(i, a[i]), fa[i] = i;
	fa[n + 1] = n + 1;
	q = read();
	while (q--){
		int op = read(), l = read(), r = read();
		if (l > r) std::swap(l, r);
		if (op == 0){
			for (register int i = l; i <= r; i = find(i + 1)){
				int t = sqrt(a[i]) + 1;
				while (1ll * t * t > a[i]) --t;
				add(i, t - a[i]), a[i] = t;
				if (a[i] == 1) fa[i] = i + 1;
			}
		}
		else printf("%lld\n", query(r) - query(l - 1));
	}
}