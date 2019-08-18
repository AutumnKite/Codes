#include <cstdio>
#include <algorithm>
int n, ans;
struct node{
	long long x;
	int y;
	bool operator < (const node &res) const {
		return y > res.y;
	}
}a[1005];
struct Linear_Basis{
	long long A[70];
	bool insert(long long x){
		for (register int i = 60; ~i; --i)
			if (x >> i & 1)
				if (!A[i]) return A[i] = x, 1;
				else x ^= A[i];
		return 0;
	}
}T;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%lld%d", &a[i].x, &a[i].y);
	std :: sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= n; ++i)
		if (T.insert(a[i].x)) ans += a[i].y;
	printf("%d", ans);
}
/*
利用线性基性质之一 -- 任意非空子集xor和不为0
贪心: 按a[i].y从大到小插入线性基
*/
 
