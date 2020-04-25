#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
int n, x, y, ans[2005];
int abs(int a){ return a > 0 ? a : -a; }
int main() {
	scanf("%d%d%d", &n, &x, &y);
	for (register int i = 1; i <= n; ++i)
		for (register int j = i + 1; j <= n; ++j){
			int d = std::min(j - i, abs(i - x) + abs(j - y) + 1);
			++ans[d];
		}
	for (register int i = 1; i < n; ++i) printf("%d\n", ans[i]);
}
