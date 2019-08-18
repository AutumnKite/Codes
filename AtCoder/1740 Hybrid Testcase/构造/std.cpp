#include <cstdio>
int T, s;
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &s);
		if (s >= 4){
			int x = s % 4, y = s / 4;
			if (x) printf("5\n%d 1 0 %d %d\n", x, y, s - x);
			else printf("5\n0 1 0 %d %d\n", y, s - 2);
		}
		if (s == 0 ||s == 1) printf("No\n");
		if (s == 2) printf("5\n0 1 1 1 2\n");
		if (s == 3) printf("5\n3 3 4 4 6\n");
	}
}
