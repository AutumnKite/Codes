#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
const int N = 1000000;
int read(){
	register int x = 0;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == 'n') return N;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
char gc(){
	register char ch = getchar();
	while (!isalpha(ch)) ch = getchar();
	return ch;
}
bool used[26];
char sta[105];
int top, L, bo[105];
void GetERR(int x){
	for (register int i = x + 1; i <= L; ++i){
		char opt = gc();
		if (opt == 'F') gc(), read(), read();
	}
	printf("ERR\n");
}
void work(){
	L = read();
	int x = read(), ans = 0, sum = 0;
	if (x == N) x = read(); else x = 0;
	memset(used, 0, sizeof used), bo[top = 0] = 1;
	for (register int i = 1; i <= L; ++i){
		char opt = gc();
		if (opt == 'E'){
			if (!top) return GetERR(i), void(0);
			if (bo[top] == 2) --sum;
			used[sta[top--]] = 0; continue;
		}
		char va = gc() - 'a';
		int x = read(), y = read();
		if (used[va]) return GetERR(i), void(0);
		used[va] = 1, sta[++top] = va;
		if (x > y || !bo[top - 1]) bo[top] = 0;
		else if (x < N && y == N) bo[top] = 2, ++sum;
		else bo[top] = 1;
		ans = std :: max(ans, sum);
	}
	if (top) return GetERR(L), void(0);
	if (ans == x) printf("Yes\n"); else printf("No\n");
}
int main(){
	int T = read();
	while (T--) work();
	getchar(), getchar();
}