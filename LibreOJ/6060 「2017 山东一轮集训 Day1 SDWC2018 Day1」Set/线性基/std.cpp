#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n;
long long sum, a[N], b[65], ans;
void insert(long long x){
	for (register int i = 60; ~i; --i)
		if (!(sum >> i & 1))
			if (x >> i & 1){
				if (!b[i]) return b[i] = x, void(0);
				x ^= b[i];
			}
	for (register int i = 60; ~i; --i)
		if (sum >> i & 1)
			if (x >> i & 1){
				if (!b[i]) return b[i] = x, void(0);
				x ^= b[i];
			}
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), sum ^= a[i];
	for (register int i = 1; i <= n; ++i) insert(a[i]);
	for (register int i = 60; ~i; --i)
		if (!(sum >> i & 1))
			if (!(ans >> i & 1))
				ans ^= b[i];
	for (register int i = 60; ~i; --i)
		if (sum >> i & 1)
			if (!(ans >> i & 1))
				ans ^= b[i];
	printf("%lld\n", sum ^ ans);
}