#include <cstdio>
#include <cstring>
#include <algorithm>
int q, x, y, ans;
int reverse(int x){
	int y = 0, s = 1;
	while (x)
		y += (!(x & 1)) * s, x >>= 1, s <<= 1;
	return y;
}
int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}
int main(){
	q = 24, x = 1;
	while (q--){
		x = (x << 1) + 1, ans = 0;
		for (register int i = 1; i < x; ++i)
			ans = std :: max(ans, gcd(x ^ i, x & i));
		printf("%d\n", ans);
	}
	getchar(), getchar();
}