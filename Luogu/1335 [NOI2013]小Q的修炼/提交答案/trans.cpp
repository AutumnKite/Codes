#include <cstdio>
#include <cstring>
char s[20], file[20];
int main(){
	freopen("answer.out", "w", stdout);
	for (register int test = 1; test <= 10; ++test){
		sprintf(file, "train%d.out", test);
		freopen(file, "r", stdin);
		while (~scanf("%s", s))
			putchar(s[0]), putchar('\\'), putchar('n');
		putchar('\n');
	}
}