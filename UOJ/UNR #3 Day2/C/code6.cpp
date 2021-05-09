#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1005;
int n, cur[N], st[N << 1], top;
struct point {
	int x, y;
	point() {}
	point(const int &x_, const int &y_) {
		x = x_;
		y = y_;
	}
	point operator-(const point &oth) const {
		return point(x - oth.x, y - oth.y);
	}
} p[N];
ll mult(const point &a, const point &b) {
	return (ll)a.x * b.y - (ll)a.y * b.x;
}
bool cmp(const point &e1, const point &e2) {
	return mult(e1 - p[1], e2 - p[1]) > 0;
}
bool cmpx(const point &e1, const point &e2) {
	return e1.x < e2.x || e1.x == e2.x && e1.y < e2.y;
}
ll dist(const point e1, const point e2) {
	ll dx = e1.x - e2.x, dy = e1.y - e2.y;
	return dx * dx + dy * dy;
}
ll ret[N << 1];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1, cmpx);
	sort(p + 2, p + n + 1, cmp);
	st[1] = 1;
	st[top = 2] = 2;
	for (int i = 3; i <= n; i++) {
		while (top > 1 &&
					 mult(p[st[top]] - p[st[top - 1]], p[i] - p[st[top - 1]]) <= 0)
			top--;
		st[++top] = i;
	}
	for (int i = 1; i <= top; i++) st[i + top] = st[i];
	st[top + top + 1] = 1;
	int i, j;
	for (i = j = 1; i <= n; i++) {
		while (dist(p[st[j + 1]], p[st[i]]) >= dist(p[st[j]], p[st[i]])) j++;
		ret[i] = max(ret[i], dist(p[st[i]], p[st[j]]));
		ret[j] = max(ret[j], dist(p[st[i]], p[st[j]]));
	}
	sort(ret + 1, ret + n + 1);
	for (i = 1; i <= n; i++) printf("%lld%c", ret[i], " \n"[i == n]);
	return 0;
}
