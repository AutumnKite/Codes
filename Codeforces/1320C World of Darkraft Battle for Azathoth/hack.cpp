#include <cstdio>
int main(){
	printf("1 1 200000\n");
	printf("2 1000000000\n");
	printf("1 1000000000\n");
	for (int i = 1; i < 200000; ++i) printf("1 1 1000\n");
	printf("1 5 1000\n");
}
