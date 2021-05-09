#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
const int N = 20005;
set<int> lp;
int n, m, rp[N], xx[N];
ll sum;
void fix(int l) {
	if (l > n) return;
	set<int>::iterator it = --lp.upper_bound(l);
	if (*it != l) xx[l] = xx[*it], rp[l] = rp[*it], rp[*it] = l - 1, lp.insert(l);
}
void fix(int l, int v) { sum += (ll)(v - xx[l]) * (rp[l] - l + 1), xx[l] = v; }
int main() {
freopen("code7.in", "r", stdin);
freopen("code7.out", "w", stdout);
	int i, o, l, r, x;
	scanf("%d%d", &n, &m);
	lp.insert(1), rp[1] = n;
	while (m--) {
		scanf("%d%d%d%d", &o, &l, &r, &x);
		fix(l);
		fix(r + 1);
		set<int>::iterator it = lp.lower_bound(l);
		while (it != lp.end() && *it <= r) fix(*it, xx[*it] * o + x), ++it;
		if (!(m & 31))
			for (i = 1; i <= n; i = rp[i] + 1)
				while (rp[i] < n && xx[rp[i] + 1] == xx[i])
					lp.erase(rp[i] + 1), rp[i] = rp[rp[i] + 1];
		printf("%lld\n", sum);
	}
	return 0;
}
