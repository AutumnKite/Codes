#include <bits/stdc++.h>

const int N = 100005;

int n, k, p[N];
std::vector<int> pos[N], rem[N];

long long m;

bool vis[N];

int tot;
int cnt[N];

int ans[N];

void add(const std::vector<int> &v) {
	for (int x : v) {
		tot += !cnt[x];
		++cnt[x];
	}
}

void del(const std::vector<int> &v) {
	for (int x : v) {
		--cnt[x];
		tot -= !cnt[x];
	}
}

void work(std::vector<int> p) {
	int len = p.size();
	int h = std::min<long long>(m / k, len);
	for (int i = len - h; i < len; ++i) {
		add(pos[p[i]]);
	}
	for (int i = 0, j = (len - h) % len; i < len; ++i, j = (j + 1) % len) {
		add(pos[p[i]]);
		del(pos[p[j]]);
		add(rem[p[j]]);
		ans[p[i]] = tot + !cnt[p[i]];
		del(rem[p[j]]);
	}
	for (int i = len - h; i < len; ++i) {
		del(pos[p[i]]);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> k >> m;
	for (int i = 0; i < n; ++i) {
		p[i] = i;
		pos[i].push_back(i);
		if (m % k) {
			rem[i].push_back(i);
		}
	}
	for (int i = 0; i < k; ++i) {
		int x, y;
		std::cin >> x >> y;
		--x, --y;
		std::swap(p[x], p[y]);
		pos[p[x]].push_back(x);
		pos[p[y]].push_back(y);
		if (i < m % k) {
			rem[p[x]].push_back(x);
			rem[p[y]].push_back(y);
		}
	}

	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			std::vector<int> c;
			for (int j = i; !vis[j]; j = p[j]) {
				vis[j] = true;
				c.push_back(j);
			}
			work(c);
		}
	}

	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] << "\n";
	}
}