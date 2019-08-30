#include <cstdio>
#include <algorithm>
int n, m, k, x[15], y[15], mxX, mxY, mnX, mnY, s;
long long ans;
void update(int x, int y){
	++s;
	mxX = std :: max(mxX, x), mnX = std :: min(mnX, x);
	mxY = std :: max(mxY, y), mnY = std :: min(mnY, y);
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	for (register int i = 0; i < k; ++i) scanf("%d%d", x + i, y + i);
	ans = 1ll * n * (n + 1) * m * (m + 1) >> 2;
	for (register int p = 1; p < (1 << k); ++p){
		mxX = mxY = 0, mnX = mnY = 100000000, s = 0;
		for (register int i = 0; i < k; ++i)
			if (p >> i & 1) update(x[i], y[i]);
		long long tmp = 1ll * mnX * mnY * (n - mxX + 1) * (m - mxY + 1);
		if (s & 1) ans -= tmp; else ans += tmp;
	}
	printf("%lld", ans);
}
