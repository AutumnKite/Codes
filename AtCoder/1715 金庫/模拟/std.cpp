#include <cstdio>
int abs(int x){
	return x > 0 ? x : -x;
}
int a, b;
int main(){
	scanf("%d%d", &a, &b);
	printf("%d\n", abs(a) + abs(a - b) + abs(b));
}
