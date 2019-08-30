#include <cstdio>
#include <cstring>
int t, n, m, c[26], p, fail[55];
char S[55], T[55];
bool check(){
	fail[1] = 0;
	for (register int i = 2, j = 0; i <= m; ++i){
		while (j && T[j + 1] != T[i]) j = fail[j];
		fail[i] = j += T[j + 1] == T[i];
	}
	for (register int i = 1, j = 0; i <= n; ++i){
		while (j && T[j + 1] != S[i]) j = fail[j];
		j += T[j + 1] == S[i];
		if (j == m) return 1;
	}
	return 0;
}
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%s%s", S + 1, T + 1), n = strlen(S + 1), m = strlen(T + 1);
		memset(c, 0, sizeof c), p = 0;
		for (register int i = 1; i <= m; ++i) ++c[T[i] - 'a'];
		for (register int i = 1; i <= n; ++i)
			if (c[S[i] - 'a']) S[++p] = S[i];
		n = p;
		if (check()) printf("YES\n"); else printf("NO\n");
	}
}
