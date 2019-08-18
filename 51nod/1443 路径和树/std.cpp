#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=300005;
int n,m,edge,to[N<<1],tw[N<<1],pr[N<<1],hd[N];
int h,t,q[N<<2],vis[N],pre[N];
long long dis[N],ans;
void addedge(int u,int v,int w){
	to[++edge]=v,tw[edge]=w,pr[edge]=hd[u],hd[u]=edge;
}
void spfa(int u){
	for (register int i=1;i<=n;++i) dis[i]=1000000000000000000ll;
	h=0,t=1,q[t]=u,vis[u]=1,dis[u]=0,pre[u]=0;
	while (h<t){
		u=q[++h],vis[u]=0;
		for (register int i=hd[u],v,w;i;i=pr[i]){
			if (dis[u]+(w=tw[i])<dis[v=to[i]]){
				dis[v]=dis[u]+w,pre[v]=w;
				if (!vis[v]) q[++t]=v,vis[v]=1;
			}
			else if (dis[v]==dis[u]+w) pre[v]=min(pre[v],w);
		}
	}
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	spfa(read());
	for (register int i=1;i<=n;++i) ans+=pre[i];
	printf("%lld",ans);
}
