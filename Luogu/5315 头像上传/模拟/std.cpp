#include <cstdio>
int n, a, b, x, y;
int main(){
	scanf("%d%d%d", &n, &a, &b);
	while (n--){
		scanf("%d%d", &x, &y);
		while (x > b || y > b) x /= 2, y /= 2;
		if (x < a || y < a) { printf("Too Young\n"); continue; }
		if (x != y) { printf("Too Simple\n"); continue; }
		printf("Sometimes Naive\n");
	}
}