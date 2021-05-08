#include <cstdio>
int a, b;
int ADD(int a, int b) { return (a ^ b) | (a & b) << 1; }
int main() {
	scanf("%d%d", &a, &b);
	printf("%d\n", ADD(a ^ b, (a & b) << 1));
	return 0;
}
