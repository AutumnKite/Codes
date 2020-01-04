#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
namespace Random_Number{
	unsigned int seed = 19260817;
	void srnd(unsigned int x){ seed = x; }
	unsigned int rnd(){
		return seed ^= seed << 19, seed ^= seed >> 7, seed ^= seed << 1;
	}
}
using namespace Random_Number;
namespace Geometry{
	const int COUNTER_CLOCKWISE = 1, CLOCKWISE = 2, ONLINE_BACK = 3, ONLINE_FRONT = 4, ON_SEGMENT = 5;
	const int IN = 2, ON = 1, OUT = 0;
	const double eps = 1e-9, pi = 3.14159265358979323846;
	bool equal(double a, double b){ return fabs(a - b) < eps; }
	struct point{
		double x, y;
		point(){}
		point(double _x, double _y){ x = _x, y = _y; }
		point operator * (const double &la) const { return point(x * la, y * la); }
		point operator / (const double &la) const { return point(x / la, y / la); }
		point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
		point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
		bool operator < (const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
		bool operator > (const point &rhs) const { return x > rhs.x || (x == rhs.x && y > rhs.y); }
		bool operator == (const point &rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
		double len2() const { return x * x + y * y; }
		double len() const { return sqrt(len2()); }
		point unit() const { return *this / len(); }
		point unit2() const { return *this / len2(); }
		double angle() const { return atan2(y, x); }
		friend double distance(const point &a, const point &b){ return (a - b).len(); }
		friend double distance2(const point &a, const point &b){ return (a - b).len2(); }
		friend double dot(const point &a, const point &b){ return a.x * b.x + a.y * b.y; }
		friend double cross(const point &a, const point &b){ return a.x * b.y - a.y * b.x; }
		void read(){ scanf("%lf%lf", &x, &y); }
		void print(char ch = '\n') const { printf("%.10lf %.10lf", x, y), putchar(ch); }
		point rotation(double th) const { return point(x * cos(th) - y * sin(th), y * cos(th) + x * sin(th)); }
		point rotation90() const { return point(-y, x); }
		friend double angle(const point &a, const point &b){ return atan2(cross(a, b), dot(a, b)); }
	};
	struct line{
		point a, b;
		line(){}
		line(point _a, point _b){ a = _a, b = _b; }
		void read(){ a.read(), b.read(); }
		void print(char ch1 = ' ', char ch2 = '\n') const { a.print(ch1), b.print(ch2); }
		point projection(const point &p) const { return a + (b - a).unit2() * dot(p - a, b - a); }
		point reflection(const point &p) const { return projection(p) * 2 - p; }
		int direction(const point &p) const {
			double t = cross(b - a, p - a);
			if (t >= eps) return COUNTER_CLOCKWISE;
			if (t <= -eps) return CLOCKWISE;
			double l1 = dot(p - a, b - a), l2 = dot(b - a, b - a);
			if (l1 <= -eps) return ONLINE_BACK;
			if (l1 > l2) return ONLINE_FRONT;
			return ON_SEGMENT;
		}
	};
	bool parallel(const line &a, const line &b){ return equal(cross(a.b - a.a, b.b - b.a), 0); }
	bool orthogonal(const line &a, const line &b){ return equal(dot(a.b - a.a, b.b - b.a), 0); }
	std::vector<point> line_cross_point(const line &a, const line &b){
		if (parallel(a, b)) return {};
		point u = a.a - b.a, v = a.b - a.a, w = b.b - b.a;
		return {a.a + v * (cross(w, u) / cross(v, w))};
	}
	bool segment_intersection(const line &a, const line &b){
		if (std::min(a.a.x, a.b.x) >= std::max(b.a.x, b.b.x) + eps) return 0;
		if (std::min(b.a.x, b.b.x) >= std::max(a.a.x, a.b.x) + eps) return 0;
		if (std::min(a.a.y, a.b.y) >= std::max(b.a.y, b.b.y) + eps) return 0;
		if (std::min(b.a.y, b.b.y) >= std::max(a.a.y, a.b.y) + eps) return 0;
		double t1, t2;
		t1 = cross(b.a - a.a, a.b - a.a), t2 = cross(b.b - a.a, a.b - a.a);
		if ((t1 >= eps && t2 >= eps) || (t1 <= -eps && t2 <= -eps)) return 0;
		t1 = cross(a.a - b.a, b.b - b.a), t2 = cross(a.b - b.a, b.b - b.a);
		if ((t1 >= eps && t2 >= eps) || (t1 <= -eps && t2 <= -eps)) return 0;
		return 1;
	}
	double distance_ps(const point &p, const line &l){
		double l1 = dot(p - l.a, l.b - l.a), l2 = dot(l.b - l.a, l.b - l.a);
		if (l1 > l2) return distance(p, l.b);
		if (l1 < 0) return distance(p, l.a);
		return fabs(cross(l.b - l.a, p - l.a)) / distance(l.a, l.b);
	}
	double distance_ss(const line &a, const line &b){
		if (segment_intersection(a, b)) return 0;
		return std::min(std::min(distance_ps(a.a, b), distance_ps(a.b, b)), 
		std::min(distance_ps(b.a, a), distance_ps(b.b, a)));
	}
	struct polygon{
		std::vector<point> g;
		polygon(){}
		polygon(int n){ g.resize(n); }
		polygon(const std::vector<point> &_g){ g = _g; }
		void read(){
			int n;
			scanf("%d", &n), g.resize(n);
			for (register int i = 0; i < n; ++i) g[i].read();
		}
		void print(){
			printf("%d\n", g.size());
			for (register int i = 0; i < g.size(); ++i) g[i].print();
		}
		void clear(){ g.clear(); }
		void resize(int n){ g.resize(n); }
		int size() const { return g.size(); }
		void push_back(point x){ return g.push_back(x); }
		void pop_back(){ g.pop_back(); }
		point& operator [] (int x){ return g[x]; }
		const point& operator [] (int x) const { return g[x]; }
		double directed_area() const {
			int n = g.size();
			double s = 0;
			for (register int i = 0; i < n; ++i) s += cross(g[i], g[(i + 1) % n]);
			return s / 2;
		}
		bool is_convex() const {
			int n = g.size();
			for (register int i = 0; i < n; ++i)
				if (cross(g[(i + 1) % n] - g[i], g[(i - 1 + n) % n] - g[i]) <= -eps) return 0;
			return 1;
		}
		int point_containment(const point &a) const {
			double k = sqrt(1.0 * rnd() / rnd());
			line l = line(a, point(a.x + 1e9, a.y + 1e9 * k));
			int n = g.size(), s = 0;
			for (register int i = 0; i < n - 1; ++i)
				if (line(g[i], g[i + 1]).direction(a) == ON_SEGMENT) return ON;
			if (line(g[n - 1], g[0]).direction(a) == ON_SEGMENT) return ON;
			for (register int i = 0; i < n - 1; ++i)
				if (segment_intersection(l, line(g[i], g[i + 1]))) ++s;
			if (segment_intersection(l, line(g[n - 1], g[0]))) ++s;
			if (s & 1) return IN; else return OUT;
		}
		void convex_hull(std::vector<point> f){
			g.clear();
			int n = f.size();
			std::sort(f.begin(), f.end());
			std::vector<point> p;
			p.push_back(f[0]);
			for (register int i = 1; i < n; ++i){
				while (p.size() > 1 && cross(f[i] - p.back(), *(++p.rbegin()) - p.back()) <= -eps)
					p.pop_back();
				p.push_back(f[i]);
			}
			for (register int i = 0; i < p.size() - 1; ++i) g.push_back(p[i]);
			std::reverse(f.begin(), f.end());
			p.clear(), p.push_back(f[0]);
			for (register int i = 1; i < n; ++i){
				while (p.size() > 1 && cross(f[i] - p.back(), *(++p.rbegin()) - p.back()) <= -eps)
					p.pop_back();
				p.push_back(f[i]);
			}
			for (register int i = 0; i < p.size() - 1; ++i) g.push_back(p[i]);
			f = g, n = f.size(), g.clear();
			int t = 0;
			for (register int i = 1; i < n; ++i)
				if (f[i].y < f[t].y || (f[i].y == f[t].y && f[i].x < f[t].x)) t = i;
			for (register int i = t; i < n; ++i) g.push_back(f[i]);
			for (register int i = 0; i < t; ++i) g.push_back(f[i]);
		}
		double convex_diamater() const {
			int n = g.size();
			double ans = 0;
			for (register int i = 0, j = 0; i < n; ++i){
				while (cross(g[i] - g[j], g[(i + 1) % n] - g[j])
				  < cross(g[i] - g[(j + 1) % n], g[(i + 1) % n] - g[(j + 1) % n]) + eps)
					j = (j + 1) % n;
				ans = std::max(ans, distance(g[j], g[i]));
				ans = std::max(ans, distance(g[j], g[(i + 1) % n]));
			}
			return ans;
		}
		polygon convex_cut(const line &l) const {
			polygon res;
			int n = g.size();
			for (register int i = 0; i < g.size(); ++i){
				point u = g[i], v = g[(i + 1) % n];
				if (cross(l.b - l.a, u - l.a) > -eps){
					res.push_back(u);
					if (cross(l.b - l.a, v - l.a) <= -eps) res.push_back(line_cross_point(line(u, v), l)[0]);
				}
				else if (cross(l.b - l.a, v - l.a) >= eps) res.push_back(line_cross_point(line(u, v), l)[0]);
			}
			return res;
		}
	};
	polygon half_plane_intersection(const std::vector<line> &l, 
	                            	double x1 = -1e9, double y1 = -1e9, double x2 = 1e9, double y2 = 1e9){
		std::vector< std::pair<double, line> > f;
		for (register int i = 0; i < l.size(); ++i) f.push_back({0, l[i]});
		f.push_back({0, line(point(x1, y1), point(x2, y1))});
		f.push_back({0, line(point(x2, y1), point(x2, y2))});
		f.push_back({0, line(point(x2, y2), point(x1, y2))});
		f.push_back({0, line(point(x1, y2), point(x1, y1))});
		int n = f.size();
		for (register int i = 0; i < f.size(); ++i)
			f[i].first = (f[i].second.b - f[i].second.a).angle();
		std::sort(f.begin(), f.end(), 
			[](const std::pair<double, line> &a, const std::pair<double, line> &b){
				if (!equal(a.first, b.first)) return a.first < b.first;
				return a.second.direction(b.second.a) == CLOCKWISE;
			});
		std::vector<line> Ql(n);
		std::vector<point> Qp(n);
		polygon res;
		int h = 0, t = 0;
		Ql[t] = f[0].second;
		for (register int i = 1; i < n; ++i)
			if (!equal(f[i].first, f[i - 1].first)){
				while (h < t && f[i].second.direction(Qp[t - 1]) == CLOCKWISE) --t;
				while (h < t && f[i].second.direction(Qp[h]) == CLOCKWISE) ++h;
				Ql[++t] = f[i].second;
				if (h < t){
					std::vector<point> tmp = line_cross_point(Ql[t], Ql[t - 1]);
					if (tmp.size()) Qp[t - 1] = tmp[0];
					else return res;
				}
			}
		while (h < t && Ql[h].direction(Qp[t - 1]) == CLOCKWISE) --t;
		while (h < t && Ql[t].direction(Qp[h]) == CLOCKWISE) ++h;
		std::vector<point> tmp = line_cross_point(Ql[t], Ql[h]);
		if (tmp.empty() || t - h < 2) return res;
		for (register int i = h; i < t; ++i) res.push_back(Qp[i]);
		res.push_back(tmp[0]);
		return res;
	}
	struct circle{
		point o;
		double r;
		circle(){}
		circle(point _o, double _r){ o = _o, r = _r; }
		void read(){ o.read(), scanf("%lf", &r); }
		void print(char ch = '\n') const { o.print(' '), printf("%.10lf", r), putchar(ch); }
		int circle_intersection(const circle &c) const {
			double d = distance(o, c.o);
			if (d >= r + c.r + eps) return 4;
			if (equal(d, r + c.r)) return 3;
			if (d >= fabs(r - c.r) + eps) return 2;
			if (equal(d, fabs(r - c.r))) return 1;
			return 0;
		}
		int point_containment(const point &p) const {
			double d = distance(o, p);
			if (d <= r - eps) return IN;
			if (d >= r + eps) return OUT;
			return ON;
		}
		std::vector<point> directed_line_cross_point(const line &l) const {
			point p = line(l.a, l.b).projection(o), v = (l.b - l.a).unit();
			double d = distance(p, o);
			if (d >= r + eps) return {};
			double t = sqrt(r * r - (p - o).len2());
			if (equal(t, 0)) return {p};
			else return {p - v * t, p + v * t};
		}
		std::vector<point> circle_cross_point(const circle &c) const {
			double d = distance(o, c.o);
			if (d <= fabs(r - c.r) - eps || d >= r + c.r + eps) return {};
			double x = (r * r - c.r * c.r + d * d) / (d * 2), h = sqrt(r * r - x * x);
			point p = o + (c.o - o).unit() * x, v = (c.o - o).unit().rotation90() * h;
			if (v == point(0, 0)) return {p}; else return {p - v, p + v};
		}
		std::vector<point> tangent(const point &p) const {
			double d = distance(o, p);
			if (d <= r - eps) return {};
			if (equal(d, r)) return {p};
			return circle_cross_point(circle(p, sqrt(d * d - r * r)));
		}
		std::vector<point> common_tangent_out(const circle &c) const {
			if (equal(r, c.r)){
				point p = (c.o - o).unit().rotation90() * r;
				return {o - p, o + p};
			}
			point p = (o * c.r - c.o * r) / (c.r - r);
			return tangent(p);
		}
		std::vector<point> common_tangent_in(const circle &c) const {
			point p = (o * c.r + c.o * r) / (r + c.r);
			return tangent(p);
		}
		std::vector<point> common_tangent(const circle &c) const {
			std::vector<point> f = common_tangent_out(c), g = common_tangent_in(c);
			for (point v : g) f.push_back(v);
			return f;
		}
		double directed_triangle_intersection(const point &a, const point &b) const {
			bool ta = a.x * a.x + a.y * a.y < r * r + eps, tb = b.x * b.x + b.y * b.y < r * r + eps;
			std::vector<point> t = circle(point(0, 0), r).directed_line_cross_point(line(b, a));
			if (ta == 1 && tb == 1) return cross(a, b) / 2;
			if (ta == 1 && tb == 0) return angle(t.front(), b) * r * r / 2 + cross(a, t.front()) / 2;
			if (ta == 0 && tb == 1) return angle(a, t.back()) * r * r / 2 + cross(t.back(), b) / 2;
			double s = angle(a, b) * r * r / 2;
			if (distance_ps(point(0, 0), line(a, b)) > r - eps) return s;
			return s + angle(t.front(), t.back()) * r * r / 2 - cross(t.front(), t.back()) / 2;
		}
		double directed_polygon_intersection(const polygon &g) const {
			int n = g.size();
			double s = 0;
			for (register int i = 0; i < n; ++i)
				s += directed_triangle_intersection(g[i] - o, g[(i + 1) % n] - o);
			return s;
		}
	};
	std::vector<circle> circumcircle(point a, point b, point c){
		point p1 = (a + b) / 2, p2 = (a + c) / 2;
		line l1 = line(p1, p1 + (a - p1).rotation90()), l2 = line(p2, p2 + (a - p2).rotation90());
		std::vector<point> t = line_cross_point(l1, l2);
		if (t.empty()) return {};
		else return {circle(t[0], distance(t[0], a))};
	}
	circle smallest_enclosing_circle(std::vector<point> v){
		srnd(time(0));
		int n = v.size();
		for (register int i = 0; i < n; ++i) std::swap(v[i], v[rnd() % n]);
		circle c = circle(point(0, 0), 0);
		for (register int i = 0; i < n; ++i)
			if (c.point_containment(v[i]) == OUT){
				c = circle(v[i], 0);
				for (register int j = 0; j < i; ++j)
					if (c.point_containment(v[j]) == OUT){
						c = circle((v[i] + v[j]) / 2, distance(v[i], v[j]) / 2);
						for (register int k = 0; k < j; ++k)
							if (c.point_containment(v[k]) == OUT)
								c = circumcircle(v[i], v[j], v[k])[0];
					}
			}
		return c;
	}
}
using namespace Geometry;
namespace Geometry_Templates{
	point p, t;
	line l, m;
	polygon g;
	circle c, d;
	std::vector<point> v, res;
	int n, q;
	double r;
	void CGL_1_A(){
		l.read(), scanf("%d", &q);
		while (q--) p.read(), l.projection(p).print();
	}
	void CGL_1_B(){
		l.read(), scanf("%d", &q);
		while (q--) p.read(), l.reflection(p).print();
	}
	void CGL_1_C(){
		l.read(), scanf("%d", &q);
		while (q--){
			p.read();
			int t = l.direction(p);
			if (t == COUNTER_CLOCKWISE) puts("COUNTER_CLOCKWISE");
			if (t == CLOCKWISE) puts("CLOCKWISE");
			if (t == ONLINE_BACK) puts("ONLINE_BACK");
			if (t == ONLINE_FRONT) puts("ONLINE_FRONT");
			if (t == ON_SEGMENT) puts("ON_SEGMENT");
		}
	}
	void CGL_2_A(){
		scanf("%d", &q);
		while (q--){
			l.read(), m.read();
			if (parallel(l, m)) puts("2");
			else if (orthogonal(l, m)) puts("1");
			else puts("0");
		}
	}
	void CGL_2_B(){
		scanf("%d", &q);
		while (q--){
			l.read(), m.read();
			if (segment_intersection(l, m)) puts("1");
			else puts("0");
		}
	}
	void CGL_2_C(){
		scanf("%d", &q);
		while (q--){
			l.read(), m.read();
			line_cross_point(l, m)[0].print();
		}
	}
	void CGL_2_D(){
		scanf("%d", &q);
		while (q--){
			l.read(), m.read();
			printf("%.10lf\n", distance_ss(l, m));
		}
	}
	void CGL_3_A(){
		g.read(), printf("%.1lf\n", g.directed_area());
	}
	void CGL_3_B(){
		g.read(), printf("%d\n", g.is_convex());
	}
	void CGL_3_C(){
		g.read();
		scanf("%d", &q);
		while (q--){
			p.read();
			printf("%d\n", g.point_containment(p));
		}
	}
	void CGL_4_A(){
		scanf("%d", &n), v.resize(n);
		for (register int i = 0; i < n; ++i) v[i].read();
		g.convex_hull(v);
		printf("%d\n", g.size());
		for (register int i = 0; i < g.size(); ++i) printf("%d %d\n", int(g[i].x), int(g[i].y));
	}
	void CGL_4_B(){
		g.read(), printf("%.10lf\n", g.convex_diamater());
	}
	void CGL_4_C(){
		g.read();
		scanf("%d", &q);
		while (q--){
			l.read();
			printf("%.10lf\n", g.convex_cut(l).directed_area());
		}
	}
	void CGL_7_A(){
		c.read(), d.read(), printf("%d\n", c.circle_intersection(d));
	}
	void CGL_7_D(){
		c.read();
		scanf("%d", &q);
		while (q--){
			l.read();
			res = c.directed_line_cross_point(l);
			std::sort(res.begin(), res.end());
			if (res.size() == 1) res.push_back(res[0]);
			res[0].print(' '), res[1].print();
		}
	}
	void CGL_7_E(){
		c.read(), d.read();
		res = c.circle_cross_point(d);
		std::sort(res.begin(), res.end());
		if (res.size() == 1) res.push_back(res[0]);
		res[0].print(' '), res[1].print();
	}
	void CGL_7_F(){
		p.read(), c.read();
		res = c.tangent(p);
		std::sort(res.begin(), res.end());
		res[0].print(), res[1].print();
	}
	void CGL_7_G(){
		c.read(), d.read();
		res = c.common_tangent(d);
		std::sort(res.begin(), res.end());
		for (register int i = 0; i < res.size(); ++i) res[i].print();
	}
	void CGL_7_H(){
		scanf("%d%lf", &n, &r);
		polygon g(n);
		for (register int i = 0; i < n; ++i) g[i].read();
		printf("%.10lf\n", fabs(circle(point(0, 0), r).directed_polygon_intersection(g)));
	}
	void Luogu_P4196(){
		scanf("%d", &n);
		std::vector<line> l;
		while (n--){
			int m;
			scanf("%d", &m), g.resize(m);
			for (register int i = 0; i < m; ++i) g[i].read();
			for (register int i = 0; i < m; ++i)
				l.push_back(line(g[i], g[(i + 1) % m]));
		}
		printf("%.3lf\n", half_plane_intersection(l).directed_area());
	}
	void Luogu_P1742(){
		scanf("%d", &n);
		std::vector<point> v(n);
		for (register int i = 0; i < n; ++i) v[i].read();
		circle c = smallest_enclosing_circle(v);
		printf("%.10lf\n%.10lf %.10lf\n", c.r, c.o.x, c.o.y);
	}
}
int main(){
	Geometry_Templates :: Luogu_P1742();
}