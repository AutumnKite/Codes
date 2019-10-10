#include <cstdio>
int x, k;
int main(){
	scanf("%d%d", &x, &k);
	for (register int i = 1; i < k; ++i) printf("%d 0\n", i);
	printf("%d 1\n", x - k + 1);
}