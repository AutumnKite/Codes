#include"tree.h"
#include<iostream>
#include<cassert>
#include<cstring>
#include<algorithm>
#include<vector>

namespace {
	int limit;
	using std::cin;
	using std::cout;
	int n, query_count;
	std::vector<std::pair<int, int>> edge;
	inline void report(const char * s){
		cout << "Wrong Answer" << '\n';
		cout << s << '\n';
		exit(0);
	}
	const int N = 140000;
	namespace kachang {
		struct Edge {
			int to, nxt;
		} e[N << 1];
		int h[N], num;
		inline void link(int x, int y) {
			e[++num] = {y, h[x]}, h[x] = num;
			e[++num] = {x, h[y]}, h[y] = num;
		}
		int dfn[N], anc[N], backup[N], cnt;
		int edge_son[N];
		int size[N];
		inline void dfs0(int x, int f = -1) {
			dfn[x] = cnt, anc[cnt] = f >= 0 ? dfn[f] : 0;
			++ cnt;
			for(int i = h[x];i;i = e[i].nxt) if(e[i].to != f)
				dfs0(e[i].to, x);
		}
		inline void init() {
			for(const auto & x : edge) {
				link(x.first, x.second);
			}
			dfs0(0);
			for(int i = 0;i < n - 1;++i) {
				const auto & x = edge[i];
				const int dx = dfn[x.first], dy = dfn[x.second];
				edge_son[i] = anc[dx] == dy ? dx : dy;
			}
			memcpy(backup, anc, n << 2);
		}
		int mem[N], * ed, * arr[N], * hehezhou[N];
	}
}
std::vector<std::vector<int>> query(std::vector<int> o) {
	if(++query_count > limit) {
		report("Too many calls");
	}
	if((int) o.size() != n - 1) {
		report("invalid size [0]");
	}
	
	using namespace kachang;
	memcpy(anc, backup, n << 2);
	memset(size, 0, n << 2);
	int tot = 1;
	for(int i = 0;i < n - 1;++i) {
		if(!o[i]) {
			anc[edge_son[i]] = edge_son[i];
			++ tot;
		}
	}
	for(int i = 0;i < n;++i) {
		++ size[anc[i] = anc[anc[i]]];
	}
	ed = mem + n;
	for(int i = 0;i < n;++i) {
		arr[i] = ed, hehezhou[i] = ed -= size[i];
	}
	std::vector<std::vector<int>> ret; ret.reserve(tot);

	for(int i = n - 1;i >= 0;--i) {
		int d = dfn[i], f = anc[d];
		*--arr[f] = i;
		if(arr[f] == hehezhou[f]) ret.emplace_back(arr[f], arr[f] + size[f]);
	}
	reverse(ret.begin(), ret.end());

	return ret;
}
int main() {
	freopen("tree.in", "r", stdin);
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> limit, edge.resize(n - 1);
	for(auto & i : edge) {
		cin >> i.first >> i.second;
		if(i.first > i.second) {
			std::swap(i.first, i.second);
		}
	}
	kachang::init();
	std::vector<std::pair<int, int>> answer = solve(n);
	if((int) answer.size() != n - 1) {
		report("invalid size [1]");
	}
	for(int i = 0;i < n - 1;++i) {
		if(answer[i].first > answer[i].second) {
			std::swap(answer[i].first, answer[i].second);
		}
	}
	sort(answer.begin(), answer.end());
	sort(edge.begin(), edge.end());
	if(answer != edge) {
		report("");
	}
	cout << "Accepted!" << '\n';
	cout << query_count << " calls" << '\n';
}
