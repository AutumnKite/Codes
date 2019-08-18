#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
int T, P, a, b, x, t, n;
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int BSGS(int a, int b){
	a %= P, b %= P;
	if (a == 0) return b == 0 ? 1 : -2;
	std :: map<int, int> M;
	int t = sqrt(P) + 1, x = 1, y;
	for (register int i = 0; i < t; ++i, x = 1ll * x * a % P)
		M[1ll * x * b % P] = i;
	y = x, M[1ll * x * b % P] = t;
	for (register int i = 1; i <= t; ++i, x = 1ll * x * y % P)
		if (M.count(x)) return i * t - M[x];
	return -2;
}
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d%d%d%d%d", &P, &a, &b, &x, &t);
		if (a == 0) n = t == x ? 0 : (t == b ? 1 : -2);
		else if (b == 0) n = x ? BSGS(a, 1ll * t * qpow(x, P - 2) % P) : (t ? -2 : 0);
		else if (a == 1) n = 1ll * qpow(b, P - 2) * (P + t - x) % P;
		else{
			int k = 1ll * qpow(P + a - 1, P - 2) * b % P;
			if ((x + k) % P == 0) n = t == x ? 0 : -2;
			else n = BSGS(a, 1ll * (t + k) * qpow(x + k, P - 2) % P);
		}
		printf("%d\n", n + 1);
	}
}
