#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

const int N = 1005;

int n, rt;
int a[N];

int fa[N], val[N], sz[N];
int ans;

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) {
		return false;
	}
	ans += sz[x] * val[y];
	fa[y] = x;
	sz[x] += sz[y];
	val[x] += val[y];
	return true;
}

int cmp(int i, int j) {
	return 1ll * val[i] * sz[j] > 1ll * val[j] * sz[i];
}

int getmx() {
	int mx = 0;
	for (int i = 1; i <= n; ++i) {
		if (find(i) == i && (!mx || cmp(i, mx))) {
			mx = i;
		}
	}
	return mx;
}

bool solve() {
	std::cin >> n >> rt;
	if (n == 0) {
		return false;
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> val[i];
		sz[i] = 1;
		fa[i] = i;
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		a[v] = u;
	}
	a[rt] = 0;
	fa[0] = 0, sz[0] = 1;
	ans = 0;
	for (int i = 1; i <= n; ++i) {
		int x = getmx();
		int y = a[x];
		merge(y, x);
	}
	std::cout << ans << std::endl;
	return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	while (solve()) {}
}
