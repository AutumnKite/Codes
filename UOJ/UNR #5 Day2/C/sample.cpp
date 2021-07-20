#include <algorithm>
#include <vector>
#include "airline.h"

long long solve(int n, int x, int y, int q, std::vector<int> P, int L){
	long long d12 = distance(1, 2);
	long long d13 = distance(1, 3);
	long long d23 = distance(2, 3);
	return std::min(std::min(d12,d13),d23);
}