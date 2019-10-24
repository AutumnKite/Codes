#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int p[8] = {2, 3, 5, 7, 11, 13, 17, 19};
int n;
long long P, f[256][256], fa[256][256], fb[256][256];
std :: vector<int> a[505];
void work(int x){
	int S = 0;
	for (register int i = 0; i < 8; ++i)
		if (x % p[i] == 0){
			S |= 1 << i;
			while (x % p[i] == 0) x /= p[i];
		}
	a[x].push_back(S);
}
void inc(long long &a, long long b){
	(a += b) >= P ? a -= P : 0;
}
int main(){
	scanf("%d%lld", &n, &P);
	for (register int i = 2; i <= n; ++i) work(i);
	f[0][0] = 1;
	for (register int i = 0; i < a[1].size(); ++i){
		for (register int S1 = 255; ~S1; --S1)
			for (register int U = 255 ^ S1, S2 = U; ~S2; S2 = S2 ? (S2 - 1) & U : -1){
				if (!(a[1][i] & S2)) inc(f[S1 | a[1][i]][S2], f[S1][S2]);
				if (!(a[1][i] & S1)) inc(f[S1][S2 | a[1][i]], f[S1][S2]);
			}
	}
	for (register int i = 2; i <= n; ++i)
		if (a[i].size()){
			for (register int S1 = 255; ~S1; --S1)
				for (register int U = 255 ^ S1, S2 = U; ~S2; S2 = S2 ? (S2 - 1) & U : -1)
					fa[S1][S2] = fb[S1][S2] = f[S1][S2];
			for (register int j = 0; j < a[i].size(); ++j)
				for (register int S1 = 255; ~S1; --S1)
					for (register int U = 255 ^ S1, S2 = U; ~S2; S2 = S2 ? (S2 - 1) & U : -1){
						if (!(a[i][j] & S2)) inc(fa[S1 | a[i][j]][S2], fa[S1][S2]);
						if (!(a[i][j] & S1)) inc(fb[S1][S2 | a[i][j]], fb[S1][S2]);
					}
			for (register int S1 = 255; ~S1; --S1)
				for (register int U = 255 ^ S1, S2 = U; ~S2; S2 = S2 ? (S2 - 1) & U : -1)
					f[S1][S2] = (fa[S1][S2] + fb[S1][S2] - f[S1][S2] + P) % P;
		}
	long long ans = 0;
	for (register int S1 = 255; ~S1; --S1)
		for (register int U = 255 ^ S1, S2 = U; ~S2; S2 = S2 ? (S2 - 1) & U : -1)
			inc(ans, f[S1][S2]);
	printf("%lld\n", ans);
}