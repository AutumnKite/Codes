#include <cstdio>
#include <algorithm>
int a, b, c, d, e, cnt, ans[20];
int main(){
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
	if (e == a || e == b) ans[++cnt] = c, ans[++cnt] = d;
	if (e == c || e == d) ans[++cnt] = a, ans[++cnt] = b;
	std :: sort(ans + 1, ans + 1 + cnt);
	cnt = std :: unique(ans + 1, ans + 1 + cnt) - ans - 1;
	printf("%d\n", cnt);
	for (register int i = 1; i <= cnt; ++i) printf("%d\n", ans[i]);
}
