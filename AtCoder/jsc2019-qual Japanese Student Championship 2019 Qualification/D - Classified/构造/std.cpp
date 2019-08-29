#include <cstdio>
int n, Log[1005];
int main(){
	scanf("%d", &n);
	Log[1] = 0;
	for (register int i = 2; i <= n * 2; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int i = 0; i < n; ++i)
		for (register int j = i + 1; j < n; ++j)
			printf("%d", Log[i ^ j] + 1), putchar(" \n"[j == n - 1]);
}
