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
const int N=2005,M=2000005;
int n,m,c[N];
int edge,to[M],pr[M],hd[N];
int in[N],h,t,q[N],dis[N],ans;
void addedge(int u,int v){
	to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void toposort(){
	h=0,t=0,ans=0;
	for (register int i=1;i<=n+m;++i) if (!in[i]) q[++t]=i,dis[i]=1;
	while (h<t){
		int u=q[++h];
		for (register int i=hd[u],v;i;i=pr[i])
			if (!(--in[v=to[i]])) q[++t]=v,dis[v]=dis[u]+(v<=n),ans=max(ans,dis[v]);
	}
	printf("%d",ans);
}
int main(){
	n=read(),m=read();
	for (register int i=1;i<=m;++i){
		int s=read();
		for (register int j=1;j<=s;++j) addedge(c[j]=read(),n+i),++in[n+i];
		for (register int j=1;j<s;++j)
			for (register int k=c[j]+1;k<c[j+1];++k)
				addedge(n+i,k),++in[k];
	}
	toposort();
}
