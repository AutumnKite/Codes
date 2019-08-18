#include <cstdio>
bool check(int x){ return (x & -x) == x; }
int H, W, n;
int main(){
	scanf("%d%d", &H, &W);
	long long tmp = 1ll * H * W - 1;
	while (tmp) ++n, tmp >>= 1;
	if (!check(W) || check(H) || check(H + 1)) printf("%lld\n", (1ll << n) - 1);
	else printf("%lld\n", (1ll << n) - W);
}
