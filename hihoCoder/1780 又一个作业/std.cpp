#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
namespace Work{
	#define N 100005
	int n, m, a[N], b[N], k;
	long long ans, s;
	long long solve(){
		n = read(), m = read(), b[0] = 1;
		for (register int i = 1; i <= n; ++i) a[i] = read();
		for (register int i = 1; i <= m; ++i) b[i] = read();
		for (register int i = 1; i <= 2; ++i){
			k = i;
			for (register int j = i + 1; j <= n; ++j) if (a[j] > a[k]) k = j;
			std :: swap(a[k], a[i]);
		}
		for (register int i = 3; i <= 4; ++i){
			k = i;
			for (register int j = i + 1; j <= n; ++j) if (a[j] < a[k]) k = j;
			std :: swap(a[k], a[i]);
		}
//		std :: sort(a + 1, a + 1 + n);
//		a[3] = a[n], a[4] = a[n - 1];
		n = std :: min(n, 4);
		k = 1;
		for (register int j = 2; j <= m; ++j) if (b[j] > b[k]) k = j;
		std :: swap(b[k], b[1]);
		k = 2;
		for (register int j = 3; j <= m; ++j) if (b[j] < b[k]) k = j;
		std :: swap(b[k], b[2]);
//		std :: sort(b + 1, b + 1 + m);
//		b[2] = b[m];
		m = std :: min(m, 2);
		ans = 1000000000000000000ll;
		for (register int k = 1; k <= n; ++k){
			s = -1000000000000000000ll;
			for (register int i = 1; i <= n; ++i)
				if (i != k)
					for (register int j = 0; j <= m; ++j)
						s = std :: max(s, 1ll * a[i] * b[j]);
//			printf("%lld\n", s);
			ans = std :: min(ans, s);
		}
		return ans;
	}
}
int main(){
	int T = read();
	for (register int _ = 1; _ <= T; ++_)
		printf("Case #%d: %lld\n", _, Work :: solve());
}
/*
1
5 4
-5 3 -2 8 6
-3 2 5 -9
*/
