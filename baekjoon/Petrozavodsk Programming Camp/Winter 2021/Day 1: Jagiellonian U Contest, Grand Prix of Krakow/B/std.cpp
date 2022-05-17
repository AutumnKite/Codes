#include <bits/stdc++.h>

template <typename Tp, typename Comp> class geometry {
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

    Tp len2() const { return x * x + y * y; }

    Tp len() const { return safe_sqrt(len2()); }

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

    Tp angle() const { return std::atan2(y, x); }

    point rotate(Tp th) const {
      return point(x * std::cos(th) - y * std::sin(th),
                   y * std::cos(th) + x * std::sin(th));
    }

    point rotate90() const { return point(-y, x); }

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
    return std::atan2(cross(a, b), dot(a, b));
  }

  static Tp distance2(const point &a, const point &b) { return (a - b).len2(); }

  static Tp distance(const point &a, const point &b) { return (a - b).len(); }

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

  static std::vector<point> segment_set_cross(const std::vector<line> &s) {
    using pointer = typename std::vector<line>::const_iterator;

    std::vector<std::tuple<Tp, bool, pointer>> op;
    for (pointer it = s.begin(); it != s.end(); ++it) {
      if (sgn(it->a.x, it->b.x) > 0) {
        op.emplace_back(it->a.x, true, it);
        op.emplace_back(it->b.x, false, it);
      } else {
        op.emplace_back(it->a.x, false, it);
        op.emplace_back(it->b.x, true, it);
      }
    }
    std::sort(op.begin(), op.end(), [&](const auto &a, const auto &b) {
      int t = sgn(std::get<0>(a), std::get<0>(b));
      if (t) {
        return t < 0;
      }
      return std::make_pair(std::get<1>(a), std::get<2>(a)) <
             std::make_pair(std::get<1>(b), std::get<2>(b));
    });

    Tp now = 0;

    std::function<bool(pointer, pointer)> cmp = [&](pointer i, pointer j) {
      int t = sgn(i->get_Y(now), j->get_Y(now));
      if (t) {
        return t < 0;
      }
      return i < j;
    };

    std::set<pointer, decltype(cmp)> S(cmp);
    bool ok = false;
    point ans;

    auto upd = [&](pointer i, pointer j) {
      auto tmp = segment_cross(*i, *j);
      if (!tmp.empty()) {
        if (!ok) {
          ok = true;
          ans = *tmp.begin();
        } else {
          ans = std::min(ans, *tmp.begin());
        }
      }
      return tmp;
    };

    for (auto p : op) {
      now = std::get<0>(p);
      if (ok && sgn(ans.x, now) < 0) {
        break;
      }
      pointer it = std::get<2>(p);
      if (std::get<1>(p)) {
        S.erase(it);
        auto nx = S.upper_bound(it);
        if (nx != S.begin() && nx != S.end()) {
          upd(*std::prev(nx), *nx);
        }
      } else {
        auto nx = S.upper_bound(it);
        if (nx != S.end()) {
          upd(it, *nx);
        }
        if (nx != S.begin()) {
          upd(*std::prev(nx), it);
        }
        S.insert(it);
      }
    }
    if (ok) {
      return {ans};
    } else {
      return {};
    }
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
    point v = h * (a.o - b.o).unit().rotate90();
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
      return circle_cross(a, circle(p, safe_sqrt(d * d - a.r * a.r)));
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(6);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<geo::line> l;
    for (int i = 0; i < n; ++i) {
      int A, B, C;
      std::cin >> A >> B >> C;
      if (B != 0) {
        double y = -1.0 * C / B;
        l.emplace_back(geo::point(0, y), geo::point(B, y - A));
      } else {
        double x = -1.0 * C / A;
        l.emplace_back(geo::point(x, 0), geo::point(x - B, A));
      }
    }

    if (n >= 3) {
      std::cout << "100.000000%\n";
      continue;
    }

    geo::polygon G{geo::point(0, 0), geo::point(m, 0),
                   geo::point(m, m), geo::point(0, m)};
    double ans = 0;
    for (int S = 0; S < (1 << n); ++S) {
      auto tmp = G;
      for (int i = 0; i < n; ++i) {
        if (S >> i & 1) {
          tmp = geo::convex_cut(tmp, l[i]);
        } else {
          tmp = geo::convex_cut(tmp, l[i].rev());
        }
      }
      ans = std::max(ans, m * m - geo::polygon_directed_area(tmp));
    }
    std::cout << 100 * ans / (m * m) << "%\n";
  }
}
