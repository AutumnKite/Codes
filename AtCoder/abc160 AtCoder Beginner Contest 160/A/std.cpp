#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
char s[10];
int main() {
	scanf("%s", s + 1);
	if (s[3] == s[4] && s[5] == s[6]) puts("Yes");
	else puts("No");
}
