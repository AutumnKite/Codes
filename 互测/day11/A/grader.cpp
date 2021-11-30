#include"tree.h"
#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
namespace run
{
	const int N=1010;
	int n,f[N],F[N];
	std::vector<int> e[N],E[N];
	int c[N],s[N];
	int cnt=0;
	void dfs(int u)
	{
		s[u]=c[u];
		for(auto v:e[u])
		{
			c[v]|=c[u]; dfs(v); s[u]+=s[v];
		}
	}
	int query(std::vector<int> a)
	{
		cnt++;
		memset(c,0,sizeof(c));
		for(auto i:a) c[i]=1;
		dfs(1); int ans=0;
		fr(i,2,n) ans+=s[i]*(s[1]-s[i]);
		return ans;
	}
	std::map<std::vector<int>,int> m; int M;
	int hash(std::vector<int> *e,int u)
	{
		std::vector<int> s;
		for(auto v:e[u]) s.push_back(hash(e,v));
		std::sort(s.begin(),s.end());
		if(!m.count(s)) m[s]=++M;
		return m[s];
	}
	int main()
	{
		n=read();
		fr(i,2,n) e[f[i]=read()].push_back(i);
		int flag=2;
		auto _f=solve(n);
		if(int(_f.size())==n-1)
		{
			fr(i,2,n) E[F[i]=_f[i-2]].push_back(i);
			fr(i,2,n) if(f[i]!=F[i]) flag=1;
			if(hash(e,1)!=hash(E,1)) flag=0;
		}
		else flag=0;
		printf("score=%.1lf, query %d times\n",std::vector<double>{0,0.4,1}[flag],cnt);
//		printf("%.10lf\n",clock()*1./CLOCKS_PER_SEC);
		return 0;
	}
}
int query(std::vector<int> a){ return run::query(a); }
int main()
{
	return run::main();
}