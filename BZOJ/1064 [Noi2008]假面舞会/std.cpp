#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=100005,M=2000005;
int n,m,edge,hd[N],to[M],tw[M],pr[M],vis[N],num[N],Max,Min,Maxx,Minn;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int abs(int a){return a>0?a:-a;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void addedge(int u,int v,int w){
	to[++edge]=v,tw[edge]=w,pr[edge]=hd[u],hd[u]=edge;
}
void dfs(int u){
	vis[u]=1;
	for (register int i=hd[u],v;i;i=pr[i])
		if (vis[v=to[i]]) Max=gcd(abs(num[u]+tw[i]-num[v]),Max);
		else num[v]=num[u]+tw[i],dfs(v);
}
void Dfs(int u){
	vis[u]=1,Maxx=max(Maxx,num[u]),Minn=min(Minn,num[u]);
	for (register int i=hd[u],v;i;i=pr[i])
		if (!vis[v=to[i]]) num[v]=num[u]+tw[i],Dfs(v);
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=m;++i){
		int u=read(),v=read();
		addedge(u,v,1),addedge(v,u,-1);
	}
	for (register int i=1;i<=n;++i) if (!vis[i]) dfs(i);
	if (Max)
		for (register int i=3;i<=Max;++i) if (Max%i==0){Min=i;break;} else;
	else{
		memset(vis,0,sizeof vis);
		memset(num,0,sizeof num);
		for (register int i=1;i<=n;++i)
			if (!vis[i]) Maxx=Minn=0,Dfs(i),Max+=Maxx-Minn+1;
		Min=3;
	}
	if (Max<3) Max=Min=-1;
	printf("%d %d",Max,Min);
}
