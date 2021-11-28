#include "hall.h"
#include<cstdio>
#include<bitset>
#include<assert.h>
#define OUTPUT
namespace
{
	std::bitset<(1<<27)>B;
	int n,K;
	const int MX=1e7;
	int cnt;
	int FLAG;
	void ask(int s)
	{
		int t=solve(n,K,s);
		if (t<0||t>=(1<<n)||__builtin_popcount(t)!=K-1||((s&t)!=t)||B[t]) FLAG=1;
		B[t]=1;
#ifdef OUTPUT
		 for (int i=0;i<n;i++) putchar('0'+(s>>i&1)); printf(" -> ");
		 for (int i=0;i<n;i++) putchar('0'+(t>>i&1)); puts("");
#undef OUTPUT
#endif
	}
	void dfs(int i,int r,int s)
	{
		if (cnt==MX) return;
		if (n-i==r) return ++cnt,ask(s|((1<<n)-(1<<i)));
		if (!r) return ++cnt,ask(s);
		dfs(i+1,r,s),dfs(i+1,r-1,1<<i|s);
	}
}

int main()
{
	scanf("%d %d",&n,&K); assert(1<=n&&n<=27&&2*K>n);
	dfs(0,K,0);
	if (FLAG) puts("WA"); else puts("OK");
	return 0;
}
