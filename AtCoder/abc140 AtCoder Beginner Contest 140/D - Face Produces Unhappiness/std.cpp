#include <cstdio>
#include <cstring>
char s[100005];
int n, k, ans;
int main(){
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1), ans = 1;
	for (register int i = 2; i <= n; ++i)
		if (s[i] != s[i - 1]) ++ans;
	if (k >= ans / 2) return printf("%d\n", n - 1), 0;
	ans -= k * 2;
	printf("%d\n", n - ans);
}