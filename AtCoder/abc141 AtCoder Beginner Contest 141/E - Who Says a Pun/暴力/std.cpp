#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 5005
int n, ans;
char a[N];
int main(){
	scanf("%d%s", &n, a + 1);
	for (register int i = 1; i <= n; ++i){
		int s = 0;
		for (register int j = 1; j <= n - i; ++j)
			a[j] == a[j + i] && s < i ? ++s, ans = std :: max(ans, s) : s = 0;
	}
	printf("%d\n", ans);
}