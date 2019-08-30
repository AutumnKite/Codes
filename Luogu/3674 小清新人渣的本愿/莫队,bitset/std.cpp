#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <cmath>
int read(){
	int x = 0;
	char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, q, a[N], block, b[N];
std :: bitset<N> B, Br;
bool ans[N];
struct query{
	int opt, bl, l, r, x, id;
	bool operator < (const query &res) const {
		return bl < res.bl || (bl == res.bl && r < res.r);
	}
}Q[N];
void add(int x){
	if (!b[x]) B[x] = 1, Br[100000 - x] = 1;
	++b[x];
}
void del(int x){
	--b[x];
	if (!b[x]) B[x] = 0, Br[100000 - x] = 0;
}
int main(){
	n = read(), q = read(), block = sqrt(n);
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= q; ++i)
		Q[i].opt = read(), Q[i].l = read(), Q[i].r = read(), Q[i].x = read(), Q[i].bl = (Q[i].l - 1) / block, Q[i].id = i;
	std :: sort(Q + 1, Q + 1 + q);
	int l = 1, r = 0;
	for (register int i = 1; i <= q; ++i){
		while (Q[i].l < l) add(a[--l]);
		while (l < Q[i].l) del(a[l++]);
		while (Q[i].r < r) del(a[r--]);
		while (r < Q[i].r) add(a[++r]);
		if (Q[i].opt == 1) ans[Q[i].id] = (B & (B << Q[i].x)).any();
		else if (Q[i].opt == 2) ans[Q[i].id] = (Br & (B << (100000 - Q[i].x))).any();
		else{
			for (register int j = 1; j * j <= Q[i].x; ++j)
				if (Q[i].x % j == 0 && B[j] && B[Q[i].x / j]) ans[Q[i].id] |= 1;
		}
	}
	for (register int i = 1; i <= q; ++i) if (ans[i]) printf("hana\n"); else printf("bi\n");
}