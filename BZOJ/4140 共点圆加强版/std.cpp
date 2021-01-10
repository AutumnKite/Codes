#include <bits/stdc++.h>

const double eps = 1e-9;

int sgn(double x) {
	return x >= eps ? 1 : (x <= -eps ? -1 : 0);
}

struct Point {
	double x, y;

	Point() : x(0), y(0) {}

	Point(double _x, double _y) : x(_x), y(_y) {}

	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	Point operator * (const double &rhs) const {
		return Point(x * rhs, y * rhs);
	}

	bool operator < (const Point &rhs) const {
		if (sgn(x - rhs.x)) {
			return sgn(x - rhs.x) < 0;
		}
		return sgn(y - rhs.y) < 0;
	}
};

double cross(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

typedef std::vector<Point> Convex;

Convex get_convex(const std::vector<Point> &a) {
	Convex res;
	for (int i = 0; i < (int)a.size(); ++i) {
		while ((int)res.size() >= 2 && sgn(cross(res.back() - res[(int)res.size() - 2], a[i] - res.back())) <= 0) {
			res.pop_back();
		}
		res.push_back(a[i]);
	}
	return res;
}

Convex merge(const Convex &a, const Convex &b) {
	std::vector<Point> res(a.size() + b.size());
	std::merge(a.begin(), a.end(), b.begin(), b.end(), res.begin());
	return get_convex(res);
}

Point get_point(const Convex &a, Point p) {
	if (p.x < 0) {
		p = p * (-1);
	}
	int l = 0, r = (int)a.size() - 2, ans = (int)a.size() - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (sgn(cross(p, a[mid + 1] - a[mid])) >= 0) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return a[ans];
}

const int N = 500005;

int q;
int top, sz[N];
Convex sta[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> q;
	int cnt = 0;
	while (q--) {
		int op;
		double a, b;
		std::cin >> op >> a >> b;
		a += cnt, b += cnt;
		if (op == 0) {
			sta[++top] = Convex(1, Point(a, b));
			sz[top] = 1;
			while (top > 1 && sz[top] == sz[top - 1]) {
				--top;
				sta[top] = merge(sta[top], sta[top + 1]);
				sz[top] += sz[top + 1];
				sta[top + 1].clear();
				sz[top + 1] = 0;
			}
		} else {
			bool flag = top > 0;
			for (int i = 1; i <= top; ++i) {
				Point p = get_point(sta[i], Point(-2 * b, 2 * a));
				if (sgn((2 * a * p.x + 2 * b * p.y) - (a * a + b * b)) < 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				std::cout << "Yes\n";
				++cnt;
			} else {
				std::cout << "No\n";
			}
		}
	}
}