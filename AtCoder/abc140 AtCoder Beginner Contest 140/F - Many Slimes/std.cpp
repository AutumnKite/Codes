#include <cstdio>
#include <algorithm>
int n, a[300005], s[300005];
bool b[300005];
int main(){
	scanf("%d", &n);
	for (register int i = 0; i < (1 << n); ++i) scanf("%d", a + i);
	std :: sort(a, a + (1 << n)), std :: reverse(a, a + (1 << n));
	b[0] = 1, s[0] = a[0];
	for (register int i = 0; i < n; ++i){
		int sz = 1 << i, k = 0;
		for (register int j = 0; j < (1 << n); ++j)
			if (!b[j] && k < sz && a[j] < s[k]) s[sz + k] = a[j], b[j] = 1, ++k;
		if (k < sz) return puts("No"), 0;
		std :: sort(s, s + (sz << 1)), std :: reverse(s, s + (sz << 1));
	}
	printf("Yes\n");
}