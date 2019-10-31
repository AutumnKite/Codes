#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <set>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, k;
std :: multiset< std :: pair<long long, int> > S;
long long ans;
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i)
		S.insert(std :: make_pair(read(), 0));
	for (register int i = (k - 1 - (n - 1) % (k - 1)) % (k - 1); i; --i)
		S.insert(std :: make_pair(0, 0));
	while (S.size() > 1){
		long long sum = 0;
		int d = 0;
		for (register int i = 1; i <= k; ++i)
			sum += S.begin() -> first, d = std :: max(d, S.begin() -> second), S.erase(S.begin());
		S.insert(std :: make_pair(sum, d + 1)), ans += sum;
	}
	printf("%lld\n%d\n", ans, S.begin() -> second);
}
