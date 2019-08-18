#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=100005,p=1000000007;
int n,k,edge,to[N<<1],pr[N<<1],hd[N],sz[N],fa[N],fac[N],inv[N],cnk,ans;
void addedge(int u,int v){
	to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void dfs(int u){
	sz[u]=1;
	for (register int i=hd[u],v;i;i=pr[i])
		if ((v=to[i])!=fa[u]) fa[v]=u,dfs(v),sz[u]+=sz[v];
}
int qpow(int a,int b){
	int s=1;
	for (;b;b&1?s=1ll*s*a%p:0,a=1ll*a*a%p,b>>=1);
	return s;
}
int C(int n,int m){
	if (m>n) return 0;
	else return 1ll*fac[n]*inv[n-m]%p*inv[m]%p;
}
void init(){
	n=read(),k=read();
	for (register int i=1;i<n;++i){
		int u=read(),v=read();
		addedge(u,v),addedge(v,u);
	}
	fac[0]=1;
	for (register int i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%p;
	inv[n]=qpow(fac[n],p-2);
	for (register int i=n;i;--i) inv[i-1]=1ll*inv[i]*i%p;
	cnk=C(n,k);
}
int calc(int s1,int s2){
	return ((cnk-C(s1,k)+p)%p-C(s2,k)+p)%p;
}
int main(){
	init(),dfs(1);
	for (register int i=2;i<=n;++i) (ans+=calc(sz[i],n-sz[i]))%=p;
	printf("%d",ans);
}
