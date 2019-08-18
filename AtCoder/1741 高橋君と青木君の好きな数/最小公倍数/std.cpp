#include <cstdio>
int a, b, n, ans;
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int lcm(int a, int b){ return a / gcd(a, b) * b; }
int main(){
	scanf("%d%d%d", &a, &b, &n);
	ans = lcm(a, b), ans *= (n - 1) / ans + 1;
	printf("%d\n", ans);
}
