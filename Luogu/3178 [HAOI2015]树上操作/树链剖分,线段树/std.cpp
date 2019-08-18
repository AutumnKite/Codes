#include <iostream>
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
#define For(i,a,b) for(int i=a;i<=b;i++)
#define DFor(i,a,b) for(int i=a;i>=b;i--)
#define cross(i,a) for(int i=hd[a];i;i=pr[i])
#define Min(a,b) a<b?a:b
#define Max(a,b) a>b?a:b
#define N 100005
#define mid ((l+r)>>1)
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
#define len (r-l+1)
#define writeln(a) write(a),putchar('\n')
using namespace std;
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
int n,m,val[N]; //input
int edge,hd[N],to[N<<1],pr[N<<1]; //graph
int fa[N],dep[N],size[N],son[N]; //dfs_1
int idc,top[N],idx[N],idt[N]; //dfs_2
struct segtree{
    LL d,mk;
}tree[N<<2];
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void build(int u,int l,int r){
    tree[u].mk=0;
    if(l==r){
        tree[u].d=val[idt[l]];
        return;
    }
    build(lson);
    build(rson);
    tree[u].d=tree[u<<1].d+tree[u<<1|1].d;
}
void pushdown(int u,int l,int r){
    tree[u<<1].d+=tree[u].mk*(mid-l+1);
    tree[u<<1|1].d+=tree[u].mk*(r-mid);
    tree[u<<1].mk+=tree[u].mk;
    tree[u<<1|1].mk+=tree[u].mk;
    tree[u].mk=0;
}
void update(int u,int l,int r,int ul,int ur,LL x){
    if(l>=ul&&r<=ur){
        tree[u].mk+=x;
        tree[u].d+=len*x;
        return;
    }
    if(tree[u].mk) pushdown(u,l,r);
    if(ul<=mid) update(lson,ul,ur,x);
    if(ur>mid) update(rson,ul,ur,x);
    tree[u].d=tree[u<<1].d+tree[u<<1|1].d;
}
LL query(int u,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr) return tree[u].d;
    LL ans=0;
    if(tree[u].mk) pushdown(u,l,r);
    if(ql<=mid) ans+=query(lson,ql,qr);
    if(qr>mid) ans+=query(rson,ql,qr);
    return ans;
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
        if(v==son[u]||v==fa[u]) continue;
        dfs(v,v);
    }
}
LL query_path(int x){
    LL ans=0;
    while(top[x]>1){
        ans+=query(1,1,n,idx[top[x]],idx[x]);
        x=fa[top[x]]; 
    }
    ans+=query(1,1,n,idx[1],idx[x]);
    return ans;
}
void update_point(int x,LL a){
    update(1,1,n,idx[x],idx[x],a);
}
void update_subtree(int x,LL a){
    update(1,1,n,idx[x],idx[x]+size[x]-1,a);
}
int main(){
    n=read(),m=read();
    For(i,1,n) val[i]=read();
    For(i,1,n-1){
        int u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    fa[1]=0,dfs(1),dfs(1,1),build(1,1,n);
    For(i,1,m){
        int k=read(),x,a;
        if(k==1) x=read(),a=read(),update_point(x,a);
        if(k==2) x=read(),a=read(),update_subtree(x,a);
        if(k==3) x=read(),writeln(query_path(x));
    }
    return 0;
}
