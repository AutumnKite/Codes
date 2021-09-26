#ifndef MYH_FENWICK_TREE
#define MYH_FENWICK_TREE 1

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>

namespace myh {

template<typename _Val, typename _VV = std::plus<_Val>, _Val _E = _Val()>
class fenwick_tree {
public:
    typedef std::size_t size_type;

protected:
    size_type n;
    std::vector<_Val> val;

    _VV fun;

public:
    fenwick_tree() : fenwick_tree(0) {}

    fenwick_tree(size_type _n) : n(_n), val(n + 1, _E) {}

    size_type size() const {
        return n;
    }

    void modify(size_type x, _Val v) {
        for (++x; x <= n; x += x & -x) {
            val[x] = fun(val[x], v);
        }
    }

    _Val query(size_type x) {
        _Val s = _E;
        for (; x; x ^= x & -x) {
            s = fun(s, val[x]);
        }
        return s;
    }
};

} // namespace myh

#endif // MYH_FENWICK_TREE
