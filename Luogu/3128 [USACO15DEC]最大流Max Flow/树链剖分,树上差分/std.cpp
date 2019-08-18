#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#define LL long long
#define For(i,a,b) for(int i=(int)(a);i<=(int)(b);i++)
#define DFor(i,a,b) for(int i=(int)(a);i>=(int)(b);i--)
#define cross(i,a) for(int i=hd[(a)];i;i=pr[i])
using namespace std;
inline LL Max(LL a,LL b){return a>b?a:b;}
inline LL Min(LL a,LL b){return a<b?a:b;}
inline LL read(){
    LL x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-') f=-1,ch=getchar();
    while (isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(LL x){
    if (x<0) putchar('-'),x=-x;
    if (x>=10) write(x/10),putchar(x%10+'0');
    else putchar(x+'0');
}
#define N 300005
int n,m,a[N],val[N],ans[N];
int edge,hd[N],pr[N<<1],to[N<<1];
int fa[N],son[N],dep[N],size[N];
int idc,top[N],idx[N],idt[N];
void addedge(int u,int v){
	to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void dfs(int u){
	size[u]=1,dep[u]=dep[fa[u]]+1;
	cross(i,u){
		int v=to[i];
		if(v==fa[u]) continue;
		fa[v]=u,dfs(v),size[u]+=size[v];
		if(!son[u]||size[v]>size[son[u]]) son[u]=v;
	}
}
void dfs(int u,int tp){
	top[u]=tp,idx[u]=++idc,idt[idc]=u;
	if(!son[u]) return;
	dfs(son[u],tp);
	cross(i,u){
		int v=to[i];
		if(v==fa[u]||v==son[u]) continue;
		dfs(v,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) u=fa[top[u]];
		else v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}
void count(int u){
	ans[u]=val[u];
	cross(i,u){
		int v=to[i];
		if(v==fa[u]) continue;
		count(v),ans[u]+=ans[v];
	}
}
int main(){
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,1,n-1){
    	int x=read(),y=read();
    	addedge(x,y),addedge(y,x);
    }
    fa[1]=0,dfs(1),dfs(1,1);
    For(i,1,m){
    	int x=read(),y=read(),LCA=lca(x,y);
    	val[x]++,val[y]++,val[LCA]--,val[fa[LCA]]--;
    }
    count(1);
    For(i,2,n) ans[a[i]]--;
    int MAX=0;
    For(i,1,n) MAX=Max(MAX,ans[i]);
    write(MAX);
    return 0;
}
