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

  static polygon half_plane_intersection(const std::vector<line> &ls,
                                         const point &min, const point &max) {
    std::vector<std::pair<Tp, line>> f;
    for (const auto &l : ls) {
      f.emplace_back(0, l);
    }
		f.emplace_back(0, line(point(min.x, min.y), point(max.x, min.y)));
		f.emplace_back(0, line(point(max.x, min.y), point(max.x, max.y)));
		f.emplace_back(0, line(point(max.x, max.y), point(min.x, max.y)));
		f.emplace_back(0, line(point(min.x, max.y), point(min.x, min.y)));
    for (auto &p : f) {
      p.first = (p.second.b - p.second.a).angle();
    }
    std::sort(f.begin(), f.end(), [&](const auto &a, const auto &b) {
      int t = sgn(a.first, b.first);
      if (t) {
        return t < 0;
      }
      return a.second.direction(b.second.a) == CLOCKWISE;
    });
    std::deque<line> Ql;
    std::deque<point> Qp;
    Ql.push_back(f[0].second);
    for (std::size_t i = 1; i < f.size(); ++i) {
      if (sgn(f[i - 1].first, f[i].first)) {
        while (!Qp.empty() && f[i].second.direction(Qp.back()) == CLOCKWISE) {
          Qp.pop_back();
          Ql.pop_back();
        }
        while (!Qp.empty() && f[i].second.direction(Qp.front()) == CLOCKWISE) {
          Qp.pop_front();
          Ql.pop_front();
        }
        auto tmp = line_cross(Ql.back(), f[i].second);
        if (tmp.empty()) {
          return polygon();
        }
        Qp.push_back(tmp[0]);
        Ql.push_back(f[i].second);
      }
    }
    while (!Qp.empty() && Ql.front().direction(Qp.back()) == CLOCKWISE) {
      Qp.pop_back();
      Ql.pop_back();
    }
    if (Ql.size() < 3) {
      return polygon();
    }
    auto tmp = line_cross(Ql.back(), Ql.front());
    if (tmp.empty()) {
      return polygon();
    }
    Qp.push_back(tmp[0]);
    return polygon(Qp.begin(), Qp.end());
  }

  static std::vector<std::size_t> half_plane_intersection_id(
      const std::vector<line> &ls, const point &min, const point &max) {
    std::vector<std::pair<std::pair<Tp, std::size_t>, line>> f;
    for (std::size_t i = 0; i < ls.size(); ++i) {
      f.emplace_back(std::pair<Tp, std::size_t>(0, i), ls[i]);
    }
    std::pair<Tp, std::size_t> add(0, -1);
		f.emplace_back(add, line(point(min.x, min.y), point(max.x, min.y)));
		f.emplace_back(add, line(point(max.x, min.y), point(max.x, max.y)));
		f.emplace_back(add, line(point(max.x, max.y), point(min.x, max.y)));
		f.emplace_back(add, line(point(min.x, max.y), point(min.x, min.y)));
    for (auto &p : f) {
      p.first.first = (p.second.b - p.second.a).angle();
    }
    std::sort(f.begin(), f.end(), [&](const auto &a, const auto &b) {
      int t = sgn(a.first.first, b.first.first);
      if (t) {
        return t < 0;
      }
      return a.second.direction(b.second.a) == CLOCKWISE;
    });
    std::deque<std::pair<std::size_t, line>> Ql;
    std::deque<point> Qp;
    Ql.emplace_back(f[0].first.second, f[0].second);
    for (std::size_t i = 1; i < f.size(); ++i) {
      if (sgn(f[i - 1].first.first, f[i].first.first)) {
        while (!Qp.empty() && f[i].second.direction(Qp.back()) == CLOCKWISE) {
          Qp.pop_back();
          Ql.pop_back();
        }
        while (!Qp.empty() && f[i].second.direction(Qp.front()) == CLOCKWISE) {
          Qp.pop_front();
          Ql.pop_front();
        }
        auto tmp = line_cross(Ql.back().second, f[i].second);
        if (tmp.empty()) {
          return std::vector<std::size_t>();
        }
        Qp.push_back(tmp[0]);
        Ql.emplace_back(f[i].first.second, f[i].second);
      }
    }
    while (!Qp.empty() && Ql.front().second.direction(Qp.back()) == CLOCKWISE) {
      Qp.pop_back();
      Ql.pop_back();
    }
    if (Ql.size() < 3) {
      return std::vector<std::size_t>();
    }
    auto tmp = line_cross(Ql.back().second, Ql.front().second);
    if (tmp.empty()) {
      return std::vector<std::size_t>();
    }
    Qp.push_back(tmp[0]);
    std::vector<std::size_t> res;
    for (const auto &p : Ql) {
      if (p.first != add.second) {
        res.push_back(p.first);
      }
    }
    return res;
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
  constexpr bool operator()(const long double &a, const long double &b) const {
    return a + 1e-9 <= b;
  }
};

using geol = geometry<long long, std::less<long long>>;
using geo = geometry<long double, double_compare>;

bool check(geol::polygon A, geol::polygon B) {
  auto cmp = [&](geol::point a, geol::point b) {
    return geol::cross(a - A[0], b - A[0]) > 0;
  };
  int n = A.size();
  for (auto q : B) {
    if (q == A[0]) {
      return true;
    }
    int x = std::lower_bound(A.begin() + 1, A.end(), q, cmp) - A.begin();
    if (x == n) {
      continue;
    }
    if (x == 1) {
      if (cmp(q, A[1])) {
        continue;
      }
      return true;
    }
    if (geol::cross(A[x] - A[x - 1], q - A[x - 1]) < 0) {
      continue;
    }
    return true;
  }
  return false;
}

geo::point trans(geol::point a) {
  return geo::point(a.x, a.y);
}

long double solve(geol::polygon A, geol::polygon B, geol::point v) {
  if (v == geol::point(0, 0)) {
    return 1e100;
  }

  auto cmp = [&](geol::point a, geol::point b) {
    return geol::cross(b - a, v) > 0;
  };

  int n = A.size();
  int l = std::min_element(A.begin(), A.end(), cmp) - A.begin();
  int r = std::max_element(A.begin(), A.end(), cmp) - A.begin();
  std::vector<geol::point> p;
  while (l != r && !cmp(A[l], A[(l + 1) % n])) {
    l = (l + 1) % n;
  }
  while (l != r) {
    p.push_back(A[l]);
    l = (l + 1) % n;
  }
  p.push_back(A[l]);

  long double res = 1e100;
  for (auto q : B) {
    int x = std::lower_bound(p.begin(), p.end(), q, cmp) - p.begin();
    if (x == (int)p.size()) {
      continue;
    }
    if (x == 0) {
      if (!cmp(q, p[0])) {
        long double t = v.x ? (long double)(p[0].x - q.x) / v.x
                            : (long double)(p[0].y - q.y) / v.y;
        if (t >= 0) {
          res = std::min(res, t);
        }
      }
      continue;
    }
    auto c = geo::line_cross(geo::line(trans(q), trans(q + v)),
                             geo::line(trans(p[x - 1]), trans(p[x])));
    assert(!c.empty());
    long double t = v.x ? (long double)(c[0].x - q.x) / v.x
                        : (long double)(c[0].y - q.y) / v.y;
    if (t >= 0) {
      res = std::min(res, t);
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int n;
  std::cin >> n;
  geol::polygon A(n);
  for (auto &p : A) {
    std::cin >> p;
  }
  int m;
  std::cin >> m;
  geol::polygon B(m);
  for (auto &p : B) {
    std::cin >> p;
  }
  geol::point vA, vB;
  std::cin >> vA >> vB;

  if (check(A, B) || check(B, A)) {
    std::cout << 0 << "\n";
    return 0;
  }

  long double ans = std::min(solve(A, B, vB - vA), solve(B, A, vA - vB));
  if (ans >= 1e50) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }
}
/*
6
6 5
7 7
6 8
5 9
3 8
4 6
5
6 3
4 2
3 1
4 -1
8 3
0 0 -5 4
*/
