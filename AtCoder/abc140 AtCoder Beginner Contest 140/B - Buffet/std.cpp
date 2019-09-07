#include <cstdio>
int n, a[25], b[25], c[25], sum;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) scanf("%d", b + i);
	for (register int i = 1; i < n; ++i) scanf("%d", c + i);
	for (register int i = 1; i <= n; ++i){
		sum += b[i];
		if (i < n && a[i + 1] == a[i] + 1) sum += c[a[i]];
	}
	printf("%d\n", sum);
}