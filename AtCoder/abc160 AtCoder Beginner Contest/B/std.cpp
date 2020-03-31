#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
int n;
int main() {
	scanf("%d", &n);
	printf("%d\n", n / 500 * 1000 + (n % 500) / 5 * 5);
}
