#include <cstdio>
#include <algorithm>
int n, a[105], b[105], sum;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i < n; ++i) scanf("%d", b + i);
	sum += a[1] = b[1], sum += a[n] = b[n - 1];
	for (register int i = 2; i < n; ++i) a[i] = std :: min(b[i - 1], b[i]), sum += a[i];
	printf("%d\n", sum);
}