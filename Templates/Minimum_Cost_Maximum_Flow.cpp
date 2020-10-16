#include <bits/stdc++.h>

struct Network {
	const int INFcap = 0x3f3f3f3f;
	const long long INFcost = 0x3f3f3f3f3f3f3f3fll;

	struct Edge {
		int u, v;
		int cap;
		long long cost;
	};

	int n, S, T;
	std::vector<Edge> edge;
	std::vector<std::vector<int>> E;

	std::vector<long long> dis;
	std::vector<int> mn;
	std::vector<int> pre;

	Network() {}

	Network(int _n) : n(_n) {
		E.resize(n);
		dis.resize(n);
		mn.resize(n);
		pre.resize(n);
	}

	void setST(int _S, int _T) {
		S = _S, T = _T;
	}

	void addEdge(int u, int v, int cap, long long cost) {
		E[u].push_back((int)edge.size()), edge.push_back({u, v, cap, cost});
		E[v].push_back((int)edge.size()), edge.push_back({v, u, 0, -cost});
	}

	bool SPFA() {
		std::fill(dis.begin(), dis.end(), INFcost);
		std::fill(mn.begin(), mn.end(), 0);
		std::fill(pre.begin(), pre.end(), -1);
		std::vector<bool> vis(n, 0);
		std::vector<int> Q;
		dis[S] = 0, mn[S] = INFcap;
		Q.push_back(S), vis[S] = 1;
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			vis[u] = 0;
			for (int id : E[u]) {
				int v = edge[id].v;
				int cap = edge[id].cap;
				long long cost = edge[id].cost;
				if (cap && dis[v] > dis[u] + cost) {
					dis[v] = dis[u] + cost;
					mn[v] = std::min(mn[u], cap);
					pre[v] = id;
					if (!vis[v]) {
						Q.push_back(v);
						vis[v] = 1;
					}
				}
			}
		}
		return dis[T] < INFcost;
	}

	void slope(int &flow, long long &cost) {
		flow = 0, cost = 0;
		while (SPFA()) {
			for (int u = T; u != S; u = edge[pre[u]].u) {
				edge[pre[u]].cap -= mn[T], edge[pre[u] ^ 1].cap += mn[T];
			}
			flow += mn[T], cost += dis[T] * mn[T];
		}
	}
};