#include <bits/stdc++.h>
#define clr(x) memset(x,0,sizeof (x))
#define For(i,a,b) for (int i=(a);i<=(b);i++)
#define Fod(i,b,a) for (int i=(b);i>=(a);i--)
#define fi first
#define se second
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define outval(x) cerr<<#x" = "<<x<<endl
#define outv(x) cerr<<#x" = "<<x<<"  "
#define outtag(x) cerr<<"--------------"#x"---------------"<<endl
#define outarr(a,L,R) cerr<<#a"["<<L<<".."<<R<<"] = ";\
	For(_x,L,R) cerr<<a[_x]<<" ";cerr<<endl;
#define outtime() cerr<<"User Time = "<<(double)clock()/CLOCKS_PER_SEC<<endl
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned uint;
typedef long double LD;
typedef vector <int> vi;
typedef pair <int,int> pii;
LL read(){
	LL x=0,f=0;
	char ch=getchar();
	while (!isdigit(ch))
		f=ch=='-',ch=getchar();
	while (isdigit(ch))
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int N=50005;
int n;
int a[N],dx[N],dy[N];
vector <int> e[N];
int dfs(int x,int pre,int *d){
	int res=x;
	for (auto y : e[x])
		if (y!=pre){
			d[y]=d[x]+1;
			int now=dfs(y,x,d);
			if (d[now]>d[res])
				res=now;
		}
	return res;
}
int main(){
	n=read();
	For(i,1,n)
		a[i]=read();
	For(i,1,n-1){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	int x=dfs(1,0,dy); memset(dx,0,sizeof dx); int y=dfs(x,0,dx);
	memset(dy,0,sizeof dy); dfs(y,0,dy);
	LL ans=0;
	For(i,1,n)
		ans=max(ans,(LL)a[i]*max(dx[i],dy[i]));
	cout<<ans<<endl;
	return 0;
}
