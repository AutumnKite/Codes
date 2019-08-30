#include <bits/stdc++.h> // hje AK ZJOI
int n, S, ans;
char s[3][3];
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i){
		for (register int j = 0; j < 3; ++j) scanf("%s", s[j]);
		if (s[0][0] == '#' && s[1][1] == '#' && s[2][2] == '#') ans ^= 2;
		if (s[0][0] == '.' && s[1][1] == '#' && s[2][2] == '#') ans ^= 1, ++S;
		if (s[0][0] == '#' && s[1][1] == '#' && s[2][2] == '.') ans ^= 1, ++S;
		if (s[0][0] == '.' && s[1][1] == '#' && s[2][2] == '.') S += 2;
		if (s[0][0] == '#' && s[1][1] == '.' && s[2][2] == '#') ++S;
	}
	printf((!ans) == (S & 1) ? "Snuke\n" : "Sothe\n");
}
// You can understand it by SG 
