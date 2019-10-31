#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <set>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
const int p[32] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
  41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
  101, 103, 107, 109, 113, 127};
long long n;
int m;
std :: set<long long> S;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= 31; ++i){
		long long v = 1;
		while (v <= n / p[i]) v *= p[i];
		S.insert(v);
	}
	for (register int i = 1; i < m; ++i){
		long long x = *S.rbegin();
		S.erase(x);
		for (register int j = 1; j <= 31; ++j)
			if (x % p[j] == 0){
				long long t = x / p[j] * p[j - 1];
				if (S.size() < m) S.insert(t);
				else if (t > *S.begin()) S.erase(S.begin()), S.insert(t);
			}
	}
	printf("%lld\n", *S.rbegin());
}