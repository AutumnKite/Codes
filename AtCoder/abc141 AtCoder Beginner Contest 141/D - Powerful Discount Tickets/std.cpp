#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <set>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m;
long long ans;
std :: multiset<int> S;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) S.insert(read());
	for (register int i = 1; i <= m; ++i){
		int t = *(--S.end());
		S.erase(--S.end());
		t >>= 1, S.insert(t);
	}
	ans = 0;
	for (int v : S) ans += v;
	printf("%lld\n", ans);
}