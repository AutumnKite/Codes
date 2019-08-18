#include <cstdio>
#include <cmath>
#include <map>
int T, opt, y, z, P;
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int inv(int a){
	if (a % P == 0) return -1;
	return qpow(a % P, P - 2);
}
int A[100005];
int BSGS(int a, int b){
	if (a % P == 0) return b % P ? -1 : 1;
	std :: map<int, int> M;
	int t = sqrt(P) + 1, x = 1, y, ans = -1;
	for (register int i = 0; i < t; ++i, x = 1ll * x * a % P)
		A[i] = 1ll * x * b % P, M[A[i]] = i;
	y = x, x = 1;
	for (register int i = 0, j; i <= t; ++i, x = 1ll * x * y % P)
		if (M.count(x)){
			j = M[x];
			if (i * t - j >= 0){ ans = i * t - j; break; }
		}
	return ans;
}
void write_ans(int x){
	if (x < 0) printf("Orz, I cannot find x!\n");
	else printf("%d\n", x);
}
int main(){
	scanf("%d%d", &T, &opt);
	while (T--){
		scanf("%d%d%d", &y, &z, &P);
		if (opt == 1) write_ans(qpow(y, z));
		if (opt == 2) write_ans(1ll * inv(y) * z % P);
		if (opt == 3) write_ans(BSGS(y, z));
	}
}

/*
1 3
0 2 3
*/
