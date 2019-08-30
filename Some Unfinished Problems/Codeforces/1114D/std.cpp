#include <cstdio>
#include <cstring>
#include <algorithm>
int n, a[5005], b[5005], sum, ans;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1, j = 1; i <= n; i = j){
		while (j <= n && a[i] == a[j]) ++j;
		++b[a[i]], ++sum, ans = std :: max(ans, b[a[i]]);
	}
	printf("%d", sum - ans);
	getchar(), getchar();
}
