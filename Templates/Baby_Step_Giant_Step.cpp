#include <cstdio>
#include <cmath>
#include <map>
int P, a, b;
int BSGS(int a, int b){
	a %= P, b %= P;
	if (a == 0) return b == 0 ? 1 : -1;
	std :: map<int, int> M;
	int t = sqrt(P) + 1, x = 1, y;
	for (register int i = 0; i < t; ++i, x = 1ll * x * a % P)
		M[1ll * x * b % P] = i;
	y = x;
	if (M.count(1) && M[1] == 0) return 0;
	for (register int i = 1; i <= t; ++i, x = 1ll * x * y % P)
		if (M.count(x)) return i * t - M[x];
	return -1;
}
void write_ans(int x){
	if (x < 0) printf("no solution\n");
	else printf("%d\n", x);
}
int main(){
	scanf("%d%d%d", &P, &a, &b);
	write_ans(BSGS(a, b));
}