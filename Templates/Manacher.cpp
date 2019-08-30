#include <cstdio>
#include <algorithm>
char buf[11000005], *ps = buf;
int n, hw[22000005], mr = 0, mid = 0, ans = 0;
char s[22000005];
int main(){
	buf[fread(buf, 1, 11000005, stdin)] = '\0', s[0] = '#';
	while (*ps >= 'a' && *ps <= 'z') s[++n] = '#', s[++n] = *ps, ++ps;
	s[++n] = '#';
	for (register int i = 1; i <= n; ++i){
		hw[i] = i <= mr ? std :: min(hw[(mid << 1) - i], mr - i + 1) : 1;
		while (s[i - hw[i]] == s[i + hw[i]]) ++hw[i];
		if (i + hw[i] - 1 > mr) mid = i, mr = i + hw[i] - 1;
		ans = std :: max(ans, hw[i] - 1);
	}
	printf("%d\n", ans);
}
