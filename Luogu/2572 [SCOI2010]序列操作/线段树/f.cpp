#include <cstdio>
#include <algorithm>
int n, m, a[100005];
int main(){
	freopen("test.in", "r", stdin);
	freopen("f.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (register int i = 0; i < n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= m; ++i){
		int opt, l, r;
		scanf("%d%d%d", &opt, &l, &r);
		if (opt <= 1) for (register int j = l; j <= r; ++j) a[j] = opt;
		if (opt == 2) for (register int j = l; j <= r; ++j) a[j] ^= 1;
		if (opt == 3){
			int s = 0;
			for (register int j = l; j <= r; ++j) s += a[j];
			printf("%d\n", s);
		}
		if (opt == 4){
			int s = 0, ans = 0;
			for (register int j = l; j <= r; ++j)
				if (a[j]) ++s, ans = std :: max(ans, s); else s = 0;
			printf("%d\n", ans);
		}
	}
}
