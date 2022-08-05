#include <bits/stdc++.h>

#include <bits/stdc++.h>

template<typename Tp, typename Comp>
class geometry {
public:
  static constexpr Tp pi = 3.14159265358979324L;

  static int sgn(const Tp &a, const Tp &b = Tp()) {
    static Comp cmp;
    return cmp(a, b) ? -1 : (cmp(b, a) ? 1 : 0);
  }

  static Tp safe_sqrt(const Tp &a) {
    if (!sgn(a)) {
      return Tp();
    } else {
      return std::sqrt(a);
    }
  }

  struct point {
    Tp x, y;

    point() : x(), y() {}

    point(const Tp &t_x, const Tp &t_y) : x(t_x), y(t_y) {}

    Tp len2() const {
      return x * x + y * y;
    }

    Tp len() const {
      return safe_sqrt(len2());
    }

    point unit2() const {
      Tp l = len2();
      if (!sgn(l)) {
        return point();
      }
      return point(x / l, y / l);
    }

    point unit() const {
      Tp l = len();
      if (!sgn(l)) {
        return point();
      }
      return point(x / l, y / l);
    }

    Tp angle() const {
      Tp t = std::atan2(y, x);
      if (sgn(t) < 0) {
        t += 2 * pi;
      }
      return t;
    }

    point rotate(Tp th) const {
      return point(x * std::cos(th) - y * std::sin(th),
                   y * std::cos(th) + x * std::sin(th));
    }

    point rotate90() const {
      return point(-y, x);
    }

    point &operator+=(const point &rhs) {
      x += rhs.x, y += rhs.y;
      return *this;
    }

    point &operator-=(const point &rhs) {
      x -= rhs.x, y -= rhs.y;
      return *this;
    }

    point &operator*=(const Tp &rhs) {
      x *= rhs, y *= rhs;
      return *this;
    }

    point &operator/=(const Tp &rhs) {
      x /= rhs, y /= rhs;
      return *this;
    }

    bool sgn_equal(const point &rhs) const {
      return !sgn(x, rhs.x) && !sgn(y, rhs.y);
    }

    friend point operator+(const point &lhs, const point &rhs) {
      return point(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend point operator-(const point &lhs, const point &rhs) {
      return point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend point operator*(const point &lhs, const Tp &rhs) {
      return point(lhs.x * rhs, lhs.y * rhs);
    }

    friend point operator*(const Tp &lhs, const point &rhs) {
      return point(lhs * rhs.x, lhs * rhs.y);
    }

    friend point operator/(const point &lhs, const Tp &rhs) {
      return point(lhs.x / rhs, lhs.y / rhs);
    }

    friend bool operator==(const point &lhs, const point &rhs) {
      return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const point &lhs, const point &rhs) {
      return lhs.x != rhs.x && lhs.y != rhs.y;
    }

    friend bool operator<(const point &lhs, const point &rhs) {
      return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }

    friend std::istream &operator>>(std::istream &in, point &p) {
      return in >> p.x >> p.y;
    }

    friend std::ostream &operator<<(std::ostream &out, const point &p) {
      return out << p.x << " " << p.y;
    }
  };

  static Tp dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
  }

  static Tp cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
  }

  static Tp angle(const point &a, const point &b) {
    Tp t = std::atan2(cross(a, b), dot(a, b));
    if (sgn(t) < 0) {
      t += 2 * pi;
    }
    return t;
  }

  static Tp distance2(const point &a, const point &b) {
    return (a - b).len2();
  }

  static Tp distance(const point &a, const point &b) {
    return (a - b).len();
  }

  enum direction_t {
    COUNTER_CLOCKWISE,
    CLOCKWISE,
    ONLINE_BACK,
    ONLINE_FRONT,
    ON_SEGMENT
  };

  struct line {
    point a, b;

    line() : a(), b() {}

    line(const point &t_a, const point &t_b) : a(t_a), b(t_b) {}

    Tp get_Y(const Tp &X) const {
      if (sgn(a.x, b.x) == 0) {
        return a.y;
      }
      return (a + (X - a.x) / (b.x - a.x) * (b - a)).y;
    }

    line rev() const {
      return line(b, a);
    }

    direction_t direction(const point &p) const {
      int t = sgn(cross(b - a, p - a));
      if (t > 0) {
        return COUNTER_CLOCKWISE;
      }
      if (t < 0) {
        return CLOCKWISE;
      }
      Tp l1 = dot(p - a, b - a);
      if (sgn(l1) < 0) {
        return ONLINE_BACK;
      }
      Tp l2 = dot(b - a, b - a);
      if (sgn(l1, l2) > 0) {
        return ONLINE_FRONT;
      }
      return ON_SEGMENT;
    }

    point midpoint() const {
      return (a + b) / 2;
    }

    line vertical_bisector() const {
      point p = midpoint();
      return line(p, p + (b - p).rotate90());
    }
  };

  static bool parallel(const line &a, const line &b) {
    return !sgn(cross(a.b - a.a, b.b - b.a));
  }

  static point projection(const line &l, const point &p) {
    return l.a + (l.b - l.a).unit2() * dot(p - l.a, l.b - l.a);
  }

  static std::vector<point> line_cross(const line &a, const line &b) {
    if (parallel(a, b)) {
      return {};
    }
    point u = a.a - b.a, v = a.b - a.a, w = b.b - b.a;
    return {a.a + cross(w, u) / cross(v, w) * v};
  }

  static std::vector<point> segment_cross(const line &a, const line &b) {
    Tp t1 = cross(b.a - a.a, a.b - a.a), t2 = cross(b.b - a.a, a.b - a.a);
    Tp t3 = cross(a.a - b.a, b.b - b.a), t4 = cross(a.b - b.a, b.b - b.a);
    if (!sgn(t1) && !sgn(t2) && !sgn(t3) && !sgn(t4)) {
      if (sgn(std::min(a.a.x, a.b.x), std::max(b.a.x, b.b.x)) > 0) {
        return {};
      }
      if (sgn(std::min(b.a.x, b.b.x), std::max(a.a.x, a.b.x)) > 0) {
        return {};
      }
      if (sgn(std::min(a.a.y, a.b.y), std::max(b.a.y, b.b.y)) > 0) {
        return {};
      }
      if (sgn(std::min(b.a.y, b.b.y), std::max(a.a.y, a.b.y)) > 0) {
        return {};
      }
      return {std::max(std::min(a.a, a.b), std::min(b.a, b.b)),
              std::min(std::max(a.a, a.b), std::max(b.a, b.b))};
    }
    if (sgn(t1) * sgn(t2) > 0) {
      return {};
    }
    if (sgn(t3) * sgn(t4) > 0) {
      return {};
    }
    return line_cross(a, b);
  }

  using polygon = std::vector<point>;

  static polygon convex_hull(std::vector<point> f) {
    if (f.empty()) {
      return polygon();
    }
    std::size_t t = 0;
    for (std::size_t i = 1; i < f.size(); ++i) {
      if (f[i].y < f[t].y || (f[i].y == f[t].y && f[i].x < f[t].x)) {
        t = i;
      }
    }
    std::rotate(f.begin(), f.begin() + t, f.end());
    std::sort(f.begin() + 1, f.end(), [&](const point &p, const point &q) {
      int tmp = sgn(cross(p - f[0], q - f[0]));
      if (tmp) {
        return tmp > 0;
      }
      return distance(p, f[0]) < distance(q, f[0]);
    });
    polygon p;
    for (std::size_t i = 0; i < f.size(); ++i) {
      while (p.size() > 1 &&
             cross(f[i] - p.back(), p[p.size() - 2] - p.back()) <= 0) {
        p.pop_back();
      }
      p.push_back(f[i]);
    }
    return p;
  }

  static polygon convex_cut(const polygon &g, const line &l) {
    polygon res;
    for (std::size_t i = 0; i < g.size(); ++i){
      point u = g[i], v = g[(i + 1) % g.size()];
      if (sgn(cross(l.b - l.a, u - l.a)) >= 0) {
        res.push_back(u);
        if (sgn(cross(l.b - l.a, v - l.a)) < 0) {
          res.push_back(line_cross(line(u, v), l)[0]);
        }
      } else if (sgn(cross(l.b - l.a, v - l.a)) > 0) {
        res.push_back(line_cross(line(u, v), l)[0]);
      }
    }
    return res;
  }

  static Tp polygon_directed_area(const polygon &g) {
    Tp s = 0;
    for (std::size_t i = 0; i < g.size(); ++i) {
      s += cross(g[i], g[(i + 1) % g.size()]);
    }
    return s / 2;
  }

  struct circle {
    point o;
    Tp r;

    circle() : o(), r() {}

    circle(const point &t_o, const Tp &t_r) : o(t_o), r(t_r) {}
  };

  static int circle_point_relation(const circle &a, const point &p) {
    return sgn(distance2(a.o, p), a.r * a.r);
  }

  static std::vector<point> circle_cross(const circle &a, const circle &b) {
    Tp d = distance(a.o, b.o);
    if (sgn(d, a.r + b.r) > 0 || sgn(d, std::abs(a.r - b.r)) < 0 || !sgn(d)) {
      return {};
    }
    Tp x = (a.r * a.r - b.r * b.r + d * d) / (d * 2);
    Tp h = safe_sqrt(a.r * a.r - x * x);
    point p = a.o + x * (b.o - a.o).unit();
    point v = h * (b.o - a.o).unit().rotate90();
    if (!sgn(v.x) && !sgn(v.y)) {
      return {p};
    } else {
      return {p - v, p + v};
    }
  }

  static std::vector<point> circle_tangent(const circle &a, const point &p) {
    Tp d = distance(a.o, p);
    int t = sgn(d, a.r);
    if (t < 0) {
      return {};
    } else if (t == 0) {
      return {p};
    } else {
      return circle_cross(circle(p, safe_sqrt(d * d - a.r * a.r)), a);
    }
  }

  static std::vector<point> circle_common_tangent_out(const circle &a,
                                                      const circle &b) {
    if (!sgn(a.r, b.r)) {
      point p = (a.o - b.o).unit().rotate90() * a.r;
      return {a.o - p, a.o + p};
    }
    point p = (a.o * b.r - b.o * a.r) / (b.r - a.r);
    return circle_tangent(a, p);
  }

  static std::vector<point> circle_line_cross(const circle &c, const line &l) {
    point p = projection(line(l.a, l.b), c.o), v = (l.b - l.a).unit();
    Tp d = distance(p, c.o);
    if (sgn(d, c.r) > 0) {
      return {};
    }
    Tp t = sqrt(c.r * c.r - (p - c.o).len2());
    if (!sgn(t)) {
      return {p};
    } else {
      return {p - v * t, p + v * t};
    }
  }
};

struct double_compare {
  constexpr bool operator()(const double &a, const double &b) const {
    return a + 1e-9 <= b;
  }
};

using geo = geometry<double, double_compare>;

std::vector<double> gauss(std::vector<std::vector<double>> a,
                          std::vector<double> b) {
  int m = a.size(), n = a[0].size();
  int now = 0;
  for (int i = 0; i < n; ++i) {
    int k = -1;
    for (int j = now; j < m; ++j) {
      if (std::abs(a[j][i]) >= 1e-9) {
        k = j;
        break;
      }
    }
    if (k != now) {
      a[now].swap(a[k]);
      std::swap(b[now], b[k]);
    }
    for (int j = 0; j < m; ++j) {
      if (j != now && std::abs(a[j][i]) >= 1e-9) {
        double t = -a[j][i] / a[now][i];
        for (int k = i; k < n; ++k) {
          a[j][k] += a[now][k] * t;
        }
        b[j] += b[now] * t;
      }
    }
    ++now;
  }
  std::vector<double> res(n);
  for (int i = 0; i < n; ++i) {
    res[i] = b[i] / a[i][i];
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int T;
  std::cin >> T;
  while (T--) {
    std::vector<geo::point> A(4), B(4);
    for (int i = 0; i < 4; ++i) {
      int x, y;
      std::cin >> x >> y;
      A[i] = geo::point(x, y);
    }
    for (int i = 0; i < 4; ++i) {
      int x, y;
      std::cin >> x >> y;
      B[i] = geo::point(x, y);
    }
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());
    double k = (B[1] - B[0]).len() / (A[1] - A[0]).len();
    double th = geo::angle(A[1] - A[0], B[1] - B[0]);
    double p = std::cos(th), q = std::sin(th);
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    for (int i = 0; i < 4; ++i) {
      a.push_back({1 - p * k, q * k});
      b.push_back(B[i].x - p * k * A[i].x + q * k * A[i].y);
      a.push_back({-q * k, 1 - p * k});
      b.push_back(B[i].y - p * k * A[i].y - q * k * A[i].x);
    }
    auto res = gauss(a, b);
    std::cout << res[0] << " " << res[1] << "\n";
  }
}
