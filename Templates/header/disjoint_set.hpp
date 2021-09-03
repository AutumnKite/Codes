#ifndef MYH_DISJOINT_SET_HPP
#define MYH_DISJOINT_SET_HPP 1

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

namespace myh {

class disjoint_set {
public:
	typedef std::size_t size_type;

protected:
	std::vector<size_type> fa;

public:
	disjoint_set(size_type n = 0) : fa(n) {
		std::iota(fa.begin(), fa.end(), 0);
	}

	size_type find(size_type x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	bool merge(size_type x, size_type y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		fa[y] = x;
		return true;
	}
};

} // namespace myh

#endif // MYH_DISJOINT_SET_HPP
