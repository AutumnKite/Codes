#include <cstdio>
#include <cstring>
int n, x, m, a, b, P;
long long ans;
struct Matrix{
	int a[2][2];
	Matrix operator * (const Matrix &res) const {
		Matrix ret;
		memset(ret.a, 0, sizeof ret.a);
		for (register int i = 0; i < 2; ++i)
			for (register int k = 0; k < 2; ++k)
				for (register int j = 0; j < 2; ++j)
					ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * res.a[k][j]) % P;
		return ret;
	}
}A, B;
Matrix qpow(Matrix a, int b){
	Matrix s = a;
	for (--b; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}
int main(){
	scanf("%d%d%d%d%d%d", &n, &x, &m, &a, &b, &P);
	A.a[0][0] = a, A.a[0][1] = 1;
	B.a[0][0] = a, B.a[0][1] = 1, B.a[1][0] = 0, B.a[1][1] = 1;
	if (m > 1) A = A * qpow(B, m - 1);
	a = A.a[0][0], b = 1ll * b * A.a[0][1] % P;
	for (register int i = 1; i <= n; ++i) ans += x, x = (1ll * a * x + b) % P;
	printf("%lld\n", ans);
}