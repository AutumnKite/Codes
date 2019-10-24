#include <cstdio>
#include <algorithm>
#include <vector>
int n, m, P, fail[25], trans[25][10];
char s[25];
void KMP(int n, char s[], int fail[], int trans[][10]){
	for (register int i = 1; i <= n; ++i){
		if (i == 1) fail[i] = 0;
		else fail[i] = trans[fail[i - 1]][s[i] ^ '0'];
		for (register int j = 0; j < 10; ++j)
			if (j == (s[i] ^ '0')) trans[i - 1][j] = i;
			else if (i == 1) trans[i - 1][j] = 0;
			else trans[i - 1][j] = trans[fail[i - 1]][j];
	}
}
typedef std :: vector< std :: vector<int> > matrix;
matrix operator * (const matrix &a, const matrix &b){
	matrix res;
	res.resize(a.size());
	for (register int i = 0; i < res.size(); ++i) res[i].resize(b[0].size());
	for (register int i = 0; i < a.size(); ++i)
		for (register int k = 0; k < b.size(); ++k)
			for (register int j = 0; j < b[k].size(); ++j)
				res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % P;
	return res;
}
matrix A, T;
matrix qpow(matrix a, int b){
	matrix s = a;
	for (--b; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}
int main(){
	scanf("%d%d%d", &n, &m, &P), scanf("%s", s + 1);
	KMP(m, s, fail, trans);
	T.resize(m);
	for (register int i = 0; i < m; ++i){
		T[i].resize(m);
		for (register int j = 0; j < 10; ++j)
			if (trans[i][j] < m) ++T[i][trans[i][j]];
	}
	A.resize(1), A[0].resize(m), A[0][0] = 1;
	A = A * qpow(T, n);
	int ans = 0;
	for (register int i = 0; i < m; ++i) (ans += A[0][i]) %= P;
	printf("%d\n", ans);
}
