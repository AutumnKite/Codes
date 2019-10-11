#include "library.h"
#include <vector>
#define N 1005
int n, S[10], Ans[10];
std :: vector<int> q, Q[10], res;
void Solve(int _n){
	n = _n, q.resize(n, 1), res.resize(n);
	for (register int i = 1; i < n; ++i){
		q[i - 1] = 0;
		if (Query(q) == 1){ res[0] = i; break; }
		q[i - 1] = 1;
	}
	if (!res[0]) res[0] = n;
	for (register int i = 0; i <= 9; ++i){
		Q[i].resize(n);
		for (register int j = 1; j <= n; ++j)
			if (j != res[0] && (j >> i & 1)) Q[i][j - 1] = 1, ++S[i];
		Ans[i] = S[i] > 1 ? Query(Q[i]) : S[i];
	}
	for (register int i = 1; i < n; ++i){
		for (register int j = 0; j <= 9; ++j){
			Q[j][res[i - 1] - 1] = 1;
			int s = Ans[j] + 1 - (S[j] ? Query(Q[j]) : 1);
			Q[j][res[i - 1] - 1] = 0;
			if (s) res[i] |= 1 << j;
		}
		for (register int j = 0; j <= 9; ++j)
			if (res[i] >> j & 1) Q[j][res[i] - 1] = 0, --S[j], Ans[j] = S[j] > 1 ? Query(Q[j]) : S[j];
	}
	Answer(res);
}