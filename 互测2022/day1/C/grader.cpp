#include<bits/stdc++.h>
#include"tree.h"
#define rb(a,b,c) for(int a=(b);a<=(c);++a)
#define rl(a,b,c) for(int a=(b);a>=(c);--a)
#define rep(a,b) for(int a=0;a<(b);++a)
#define LL long long
#define II(a,b) make_pair(a,b)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define check_min(a,b) a=min(a,b)
#define check_max(a,b) a=max(a,b)
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
namespace judger
{
	const int N=1005;
	int n,d[N][N],f[N],c1,c2,A,B;
	vector<int>e[N];
	multiset<pair<int,int>>s,t;
	int fa(int x){return x==f[x]?x:f[x]=fa(f[x]);}
	void dfs(int u,int f,int b,int w)
	{
		d[b][u]=w;
		for(auto v:e[u])
			if(v!=f)
				dfs(v,u,b,w+1);
	}
	void init()
	{
		scanf("%d",&n);
		cin>>A>>B;
		if(n<1||n>1000)
		{
			puts("Invalid n");
			exit(0);
		}
		for(int i=1;i<=n;i++)
			f[i]=i;
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(u<1||u>n||v<1||v>n||fa(u)==fa(v))
			{
				cerr<<u<<" "<<v<<endl;
				puts("Invalid edge");
				exit(0);
			}
			if(u>v) swap(u,v);
			s.insert({u,v});
			e[u].push_back(v);
			e[v].push_back(u);
			f[fa(u)]=fa(v);
		}
		for(int i=1;i<=n;i++)
			dfs(i,0,i,0);
	}
	int ask(int u,vector<int>v)
	{
		c1++;
		c2+=v.size();
		if(c1>A)
		{
			puts("Too many queries");
			exit(0);
		}
		if(c2>B)
		{
			puts("The sum is too large");
			exit(0);
		}
		if(u<1||u>n)
		{
			puts("Invalid ask");
			exit(0);
		}
		sort(v.begin(),v.end());
		for(int i=1;i<v.size();i++)
		{
			if(v[i]==v[i-1])
			{
				puts("Invalid ask");
				exit(0);
			}
		}
		int s=0;
		for(auto i:v)
		{
			if(i<1||i>n)
			{
				puts("Invalid ask");
				exit(0);
			}
			s+=d[u][i];
		}
		return s;
	}
	void answer(int u,int v)
	{
		if(u>v) swap(u,v);
        if(t.size()==n-1){
            puts("Different tree");
            exit(0);
        }
        if(t.count(II(u,v))){
            puts("Different tree");
            exit(0);
        }
		t.insert({u,v});
 	}
	void chk()
	{
		if(s==t)
			puts("Correct"),cout<<"cnt="<<c1<<' '<<"sum="<<c2<<endl;
		else
			puts("Different tree");
	}
}
int ask(int u,std::vector<int>v) {return judger::ask(u,v);}
void answer(int u,int v) {judger::answer(u,v);}
int main(){
    judger::init();
    solver(judger::n,judger::A,judger::B);
    judger::chk();
    return 0;
}