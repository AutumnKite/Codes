#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<Val>,
         typename Comp = std::less<Val>>
class seg_tree {
public:
  typedef std::size_t size_type;

private:
  static size_type enlarge(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const size_type n, en;

  VV vv;
  Comp comp;

  std::vector<Val> val;

  void up(size_type u) {
    val[u] = vv(val[u << 1], val[u << 1 | 1]);
  }

  template<typename Iter>
  void build(size_type u, size_type l, size_type r, Iter &it) {
    if (l + 1 == r) {
      val[u] = Val(*it);
      ++it;
      return;
    }
    size_type mid = (l + r) >> 1;
    build(u << 1, l, mid, it);
    build(u << 1 | 1, mid, r, it);
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
              size_type x, const Val &v) {
    if (l + 1 == r) {
      val[u] = v;
      return;
    }
    size_type mid = (l + r) >> 1;
    if (x < mid) {
      modify(u << 1, l, mid, x, v);
    } else {
      modify(u << 1 | 1, mid, r, x, v);
    }
    up(u);
  }

  Val query(size_type u, size_type l, size_type r, 
            size_type L, size_type R) {
    if (L <= l && r <= R) {
      return val[u];
    }
    size_type mid = (l + r) >> 1;
    if (R <= mid) {
      return query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R);
    } else {
      return vv(query(u << 1, l, mid, L, R), 
                query(u << 1 | 1, mid, r, L, R));
    }
  }

  size_type lower_bound(size_type u, size_type l, size_type r, 
                        size_type L, size_type R,
                        Val &pre, const Val &v) {
    if (L <= l && r <= R) {
      const Val &tmp = vv(pre, val[u]);
      if (comp(tmp, v)) {
        pre = tmp;
        return r;
      }
    }
    if (l + 1 == r) {
      return l;
    }
    size_type mid = (l + r) >> 1;
    if (R <= mid) {
      return lower_bound(u << 1, l, mid, L, R, pre, v);
    } else if (L >= mid) {
      return lower_bound(u << 1 | 1, mid, r, L, R, pre, v);
    } else {
      size_type res = lower_bound(u << 1, l, mid, L, R, pre, v);
      if (res < mid) {
        return res;
      } else {
        return lower_bound(u << 1 | 1, mid, r, L, R, pre, v);
      }
    }
  }

  size_type upper_bound(size_type u, size_type l, size_type r, 
                        size_type L, size_type R,
                        Val &pre, const Val &v) {
    if (L <= l && r <= R) {
      const Val &tmp = vv(pre, val[u]);
      if (!comp(v, tmp)) {
        pre = tmp;
        return r;
      }
    }
    if (l + 1 == r) {
      return l;
    }
    size_type mid = (l + r) >> 1;
    if (R <= mid) {
      return upper_bound(u << 1, l, mid, L, R, pre, v);
    } else if (L >= mid) {
      return upper_bound(u << 1 | 1, mid, r, L, R, pre, v);
    } else {
      size_type res = upper_bound(u << 1, l, mid, L, R, pre, v);
      if (res < mid) {
        return res;
      } else {
        return upper_bound(u << 1 | 1, mid, r, L, R, pre, v);
      }
    }
  }

public:
  seg_tree() : seg_tree(0) {}

  seg_tree(size_type t_n, VV t_vv = VV(), Comp t_comp = Comp())
  : n(t_n), en(enlarge(n)), 
    vv(t_vv), comp(t_comp), val(en << 1) {}

  template<typename Iter>
  seg_tree(Iter first, Iter last, VV t_vv = VV(), Comp t_comp = Comp())
  : seg_tree(last - first, t_vv, t_comp) {
    if (n) {
      build(1, 0, n, first);
    }
  }

  size_type size() const {
    return n;
  }

  VV func_vv() const {
    return vv;
  }

  Comp func_comp() const {
    return comp;
  }

  void modify(size_type x, const Val &v) {
    modify(1, 0, n, x, v);
  }

  Val query(size_type l, size_type r) {
    if (l < r) {
      return query(1, 0, n, l, r);
    } else {
      return Val();
    }
  }

  size_type lower_bound(size_type l, size_type r, Val E, const Val &v) {
    return lower_bound(1, 0, n, l, r, E, v);
  }

  size_type upper_bound(size_type l, size_type r, Val E, const Val &v) {
    return upper_bound(1, 0, n, l, r, E, v);
  }
};

namespace zxyfg{
  typedef double db;
  struct point{
    db x,y;
    point():x(),y(){}
    point(db t_x,db t_y):x(t_x),y(t_y){}
    inline point operator + (const point &p)const{return (point){x+p.x,y+p.y};}
    inline point operator - (const point &p)const{return (point){x-p.x,y-p.y};}
    inline point operator * (const db &v)const{return (point){x*v,y*v};}
    inline point operator / (const db &v)const{return (point){x/v,y/v};}
    inline db operator * (const point &p)const{return x*p.x+y*p.y;}
    inline db dis(){return sqrt(x*x+y*y);}
    inline db dis2(){return x*x+y*y;}
    inline point rot90(){return (point){y,-x};}
  };
  inline db cross(point a,point b){return a.x*b.y-a.y*b.x;}
  inline db dis(point a,point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
  const db eps = 1e-10;
  inline int sign(db x){
    if (fabs(x)<=eps) return 0;
    return x>0?1:-1;
  }

  struct line{
    point s,t;
  };
  inline point cross(line a,line b) {
      point u=a.s-b.s,v=a.t-a.s,w=b.t-b.s;
      db t=cross(w,u)/cross(v,w);
      return a.s+v*t;
  }

  struct circle{
    point o;
    db r;
  };
  inline bool In(point a,circle b){return sign(dis(a,b.o)-b.r)<=0;}
  inline circle circumcircle(point A,point B,point C){
    point AB=B-A,BC=C-B,mAB=(A+B)/2,mBC=(B+C)/2;
    line a=(line){mAB,mAB+AB.rot90()};
    line b=(line){mBC,mBC+BC.rot90()};
    circle ret;ret.o=cross(a,b),ret.r=dis(ret.o,A);
    return ret;
  }

  inline double solve(std::vector<point>v){
    std::mt19937 rnd(time(0));
    std::shuffle(v.begin(),v.end(),rnd);
    circle ans;ans.o.x=ans.o.y=ans.r=0;
    int n=v.size();
    for(int i=0;i<n;++i) if (!In(v[i],ans)){
      ans.o=v[i],ans.r=0;
      for(int j=0;j<i;++j) if (!In(v[j],ans)){
        ans.o=(v[i]+v[j])/2,ans.r=dis(v[i],v[j])/2;
        for(int k=0;k<j;++k) if (!In(v[k],ans)) ans=circumcircle(v[i],v[j],v[k]);
      }
    }
    return ans.r;
  }
}

struct point {
  int x, y;

  point() : x(), y() {}

  point(int t_x, int t_y) : x(t_x), y(t_y) {}

  point operator+(const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }

  point operator-(const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }

  bool operator<(const point &rhs) const {
    return x < rhs.x;
  }
};

long long cross(const point &a, const point &b) {
  return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

struct node {
  std::vector<point> A, B;

  node() : A(), B() {}

  node(point p) : A(1, p), B(1, p) {}

  node operator+(const node &rhs) const {
    node s;
    std::vector<point> nA(A.size() + rhs.A.size());
    std::merge(A.begin(), A.end(), rhs.A.begin(), rhs.A.end(), nA.begin());
    s.A.reserve(nA.size());
    for (auto p : nA) {
      while (s.A.size() > 1 &&
             cross(s.A.back() - s.A[s.A.size() - 2], p - s.A.back()) <= 0) {
        s.A.pop_back();
      }
      s.A.push_back(p);
    }
    std::vector<point> nB(B.size() + rhs.B.size());
    std::merge(B.begin(), B.end(), rhs.B.begin(), rhs.B.end(), nB.begin());
    s.B.reserve(nB.size());
    for (auto p : nB) {
      while (s.B.size() > 1 &&
             cross(s.B.back() - s.B[s.B.size() - 2], p - s.B.back()) >= 0) {
        s.B.pop_back();
      }
      s.B.push_back(p);
    }
    return s;
  }
};

// #define DEBUG

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef DEBUG
  std::mt19937 rnd(time(0));
  assert(freopen("data.out", "w", stdout));
#endif

  int test;
#ifdef DEBUG
  test = 3;
#else
  std::cin >> test;
#endif
  while (test--) {
    int n, q;
#ifdef DEBUG
    n = q = 100000;
#else
    std::cin >> n >> q;
#endif
    std::vector<point> a(n);
    for (int i = 0; i < n; ++i) {
#ifdef DEBUG
      a[i].x = rnd() % 100000000 + 1;
      a[i].y = rnd() % 100000000 + 1;
#else
      std::cin >> a[i].x >> a[i].y;
#endif
    }
    seg_tree<node> T(a.begin(), a.end());
    while (q--) {
      int op;
#ifdef DEBUG
      op = rnd() % 2 + 1;
#else
      std::cin >> op;
#endif
      if (op == 1) {
        int k, x, y;
#ifdef DEBUG
        k = rnd() % n + 1;
        x = rnd() % 100000000 + 1;
        y = rnd() % 100000000 + 1;
#else
        std::cin >> k >> x >> y;
#endif
        --k;
        T.modify(k, point(x, y));
      } else {
        int l, r;
#ifdef DEBUG
        l = 2;
        r = n - 1;
#else
        std::cin >> l >> r;
#endif
        --l;
        auto tmp = T.query(l, r);
        tmp.A.pop_back();
        tmp.B.erase(tmp.B.begin());
        std::vector<zxyfg::point> S;
        for (auto p : tmp.A) {
          S.emplace_back(p.x, p.y);
        }
        for (auto p : tmp.B) {
          S.emplace_back(p.x, p.y);
        }
        int ans = ceil(zxyfg::solve(S));
        std::cout << ans << "\n";
      }
    }
  }
}
