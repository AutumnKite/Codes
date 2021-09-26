#ifndef MYH_SEG_TREE_HPP
#define MYH_SEG_TREE_HPP 1

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>

namespace myh {

template<typename _Val, 
         typename _VV = std::plus<>>
class seg_tree {
public:
    typedef std::size_t size_type;

private:
    constexpr static size_type enlarge(size_type n) {
        size_type res = 1;
        while (res < n) {
            res <<= 1;
        }
        return res;
    }

protected:
    const size_type n, en;

    _VV fun_vv;

    std::vector<_Val> val;

    void up(size_type u) {
        val[u] = fun_vv(val[u << 1], val[u << 1 | 1]);
    }

    template<typename T>
    void build(size_type u, size_type l, size_type r, 
               const std::vector<T> &a) {
        if (l + 1 == r) {
            val[u] = _Val(a[l]);
            return;
        }
        size_type mid = (l + r) >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid, r, a);
        up(u);
    }

    void modify(size_type u, size_type l, size_type r, 
                size_type x, const _Val &v) {
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

    _Val query(size_type u, size_type l, size_type r, 
               size_type L, size_type R) const {
        if (L <= l && r <= R) {
            return val[u];
        }
        size_type mid = (l + r) >> 1;
        if (R <= mid) {
            return query(u << 1, l, mid, L, R);
        } else if (L >= mid) {
            return query(u << 1 | 1, mid, r, L, R);
        } else {
            return fun_vv(query(u << 1, l, mid, L, R), 
                          query(u << 1 | 1, mid, r, L, R));
        }
    }

public:
    seg_tree() : seg_tree(0) {}

    seg_tree(size_type _n)
    : n(_n), en(enlarge(n)), val(en << 1) {}

    template<typename T>
    seg_tree(const std::vector<T> &a)
    : n(a.size()), en(enlarge(n)), val(en << 1) {
        if (n) {
            build(1, 0, n, a);
        }
    }

    size_type size() const {
        return n;
    }

    void modify(size_type x, const _Val &v) {
        modify(1, 0, n, x, v);
    }

    _Val query(size_type l, size_type r) const {
        if (l < r) {
            return query(1, 0, n, l, r);
        } else {
            return _Val();
        }
    }
};

} // namespace myh

#endif // MYH_SEG_TREE_HPP
