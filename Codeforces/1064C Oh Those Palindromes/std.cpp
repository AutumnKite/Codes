#include <cstdio>
#include <cstring>
#include <algorithm>
int n;
char c[1000005];
int main(){
	scanf("%s", c), n = strlen(c);
	std :: sort(c, c + n);
	printf("%s", c);
}