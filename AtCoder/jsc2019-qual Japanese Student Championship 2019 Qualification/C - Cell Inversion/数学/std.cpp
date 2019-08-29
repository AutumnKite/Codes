#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define P 1000000007
int n, d, ans;
char s[200005];
int main(){
	scanf("%d%s", &n, s + 1);
	for (register int i = 1; i <= (n << 1); ++i)
		if ((i & 1) ^ (s[i] == 'B')) s[i] = 'R'; else s[i] = 'L';
	ans = 1;
	for (register int i = 1; i <= (n << 1); ++i)
		if (s[i] == 'L') ++d;
		else{
			if (!d) return printf("0\n"), 0;
			ans = 1ll * ans * d % P, --d;
		}
	if (d) return printf("0\n"), 0;
	for (register int i = 1; i <= n; ++i) ans = 1ll * ans * i % P;
	printf("%d\n", ans);
}
