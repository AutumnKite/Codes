#include <cstdio>
const char s[] = "DiscoPresentsDiscoveryChannelProgrammingContest2016";
int n;
int main(){
	scanf("%d", &n);
	for (register int i = 0; i < 51; ++i)
		putchar(s[i]), (i + 1) % n == 0 && i < 50 ? putchar('\n') : 0;
	putchar('\n');
}
