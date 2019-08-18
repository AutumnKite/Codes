#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n;
struct node{
	int val, id;
	bool operator < (const node &b) const {
		return val > b.val || val == b.val && id < b.id;
	}
}a[100005];
long long ans[100005];
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = (node){read(), i};
	std :: sort(a + 1, a + 1 + n);
	for (register int i = 1, j, k = 0x3f3f3f3f; i <= n; i = j){
		for (j = i; j <= n && a[j].val == a[i].val; ++j) ;
		k = std :: min(k, a[i].id);
		ans[k] += 1ll * (j - 1) * (a[i].val - a[j].val);
	}
	for (register int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
}