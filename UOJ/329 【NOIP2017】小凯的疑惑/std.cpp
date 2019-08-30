#include <cstdio>
long long a, b;
int main(){
	scanf("%lld%lld", &a, &b);
	printf("%lld", a * b - a - b);
}