#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <set>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 5005
const int B1 = 233, P1 = 382538579, B2 = 331, P2 = 952959323;
int pw1[N], pw2[N];
struct node{
	int H1, H2;
	node(int _H1 = 0, int _H2 = 0){ H1 = _H1, H2 = _H2; }
	bool operator < (const node &rhs) const {
		return H1 < rhs.H1 || (H1 == rhs.H1 && H2 < rhs.H2);
	}
	bool operator == (const node &rhs) const {
		return H1 == rhs.H1 && H2 == rhs.H2;
	}
	node operator + (const char ch) const {
		return node((1ll * H1 * B1 + ch) % P1, (1ll * H2 * B2 + ch) % P2);
	}
	node operator - (const node &rhs) const {
		return node((H1 - rhs.H1 + P1) % P1, (H2 - rhs.H2 + P2) % P2);
	}
	node operator << (const int x) const {
		return node(1ll * H1 * pw1[x] % P1, 1ll * H2 * pw2[x] % P2);
	}
}h[N];
int n;
char a[N];
int main(){
	scanf("%d%s", &n, a + 1);
	pw1[0] = pw2[0] = 1;
	for (register int i = 1; i <= n; ++i)
		pw1[i] = 1ll * pw1[i - 1] * B1 % P1, pw2[i] = 1ll * pw2[i - 1] * B2 % P2;
	for (register int i = 1; i <= n; ++i) h[i] = h[i - 1] + a[i];
	for (register int len = n >> 1; len; --len){
		std :: set<node> S;
		for (register int i = len << 1; i <= n; ++i){
			S.insert(h[i - len] - (h[i - (len << 1)] << len));
			if (S.count(h[i] - (h[i - len] << len))) return printf("%d\n", len), 0;
		}
	}
	printf("0\n");
}
