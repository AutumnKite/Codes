#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int main(){
	srand(time(0));
	int T = 100, n = 1000000;
	printf("%d\n", T);
	while (T--) printf("%d %d %d %d\n", rnd(0, n), rnd(0, n), rnd(0, n), rnd(0, n));
}