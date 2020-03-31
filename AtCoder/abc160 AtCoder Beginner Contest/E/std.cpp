#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N = 300005;
int c[2], A, B, C, n;
struct node{
	int v, k;
	bool operator < (const node &rhs) const { return v > rhs.v; }
}a[N];
int main(){
	scanf("%d%d%d%d%d", &c[0], &c[1], &A, &B, &C);
	for (register int i = 1; i <= A; ++i) scanf("%d", &a[++n].v), a[n].k = 0;
	for (register int i = 1; i <= B; ++i) scanf("%d", &a[++n].v), a[n].k = 1;
	for (register int i = 1; i <= C; ++i) scanf("%d", &a[++n].v), a[n].k = 2;
	std::sort(a + 1, a + 1 + n);
	int s[3] = {0, 0, 0};
	long long sum = 0;
	for (register int i = 1; i <= n; ++i){
		if (a[i].k == 2 || s[a[i].k] < c[a[i].k]) ++s[a[i].k], sum += a[i].v;
		if (s[0] + s[1] + s[2] >= c[0] + c[1]) break;
	}
	printf("%lld\n", sum);
}
