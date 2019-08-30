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
#define INF 1000000000
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
int n,m,s,mod,val[N]; //input
int edge,hd[N],to[N<<1],pr[N<<1]; //graph
int fa[N],dep[N],size[N],son[N]; //dfs_1
int idc,top[N],idx[N],idt[N]; //dfs_2
struct node{
    int d1,d2;
    node(int a=0,int b=0){d1=a,d2=b;}
}tree[N<<2];
node operator +(const node&x,const node&y){
     return node(x.d1+y.d1,max(x.d2,y.d2));
}
void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
void build(int u,int l,int r){
    if(l==r){
        tree[u].d1=tree[u].d2=val[idt[l]];
        return;
    }
    build(lson),build(rson);
    tree[u]=tree[u<<1]+tree[u<<1|1];
}
void update(int u,int l,int r,int ux,int x){
    if(l==r){
        tree[u].d1=tree[u].d2=x;
        return;
    }
    if(ux<=mid) update(lson,ux,x); else update(rson,ux,x);
    tree[u]=tree[u<<1]+tree[u<<1|1];
}
node query(int u,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr) return tree[u];
    node ans=node(0,-INF);
    if(ql<=mid) ans=ans+query(lson,ql,qr);
    if(qr>mid) ans=ans+query(rson,ql,qr);
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
void update_point(int x,int z){
    update(1,1,n,idx[x],z);
}
node query_path(int x,int y){
    node ans=node(0,-INF);
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans=ans+query(1,1,n,idx[top[x]],idx[x]);
        x=fa[top[x]]; 
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans=ans+query(1,1,n,idx[x],idx[y]);
    return ans;
}
int main(){
    n=read();
    For(i,1,n-1){
        int u=read(),v=read();
        addedge(u,v),addedge(v,u);
    }
    For(i,1,n) val[i]=read();
    m=read(),fa[1]=0,dfs(1),dfs(1,1),build(1,1,n);
    For(i,1,m){
        string s;cin>>s;
        int x,y,z;
        if(s=="CHANGE") x=read(),z=read(),update_point(x,z);
        else x=read(),y=read(),writeln(s=="QSUM"?query_path(x,y).d1:query_path(x,y).d2);
    }
    return 0;
}
