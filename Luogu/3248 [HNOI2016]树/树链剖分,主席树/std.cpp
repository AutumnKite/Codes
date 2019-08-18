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
inline char GET_CHAR(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
#define CH ch=GET_CHAR()
inline LL read(){
    LL x=0;int ch,f=1;CH;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) CH;
    if (ch=='-') f=-1,CH;
    while (isdigit(ch)) x=(x<<1)+(x<<3)+ch-'0',CH;
    return x*f;
}
inline void write(LL x){
    if (x<0) putchar('-'),x=-x;
    if (x>=10) write(x/10),putchar(x%10+'0');
    else putchar(x+'0');
}
#define N 100005
#define M 100005
int n,m,q,cnt,a[N];
int edge,to[N<<1],pr[N<<1],tw[N<<1],hd[N];
LL S[M],A[M],B[M];
inline void addedge(int u,int v,int w){
    to[++edge]=v,tw[edge]=w,pr[edge]=hd[u],hd[u]=edge;
}
int idx,dep[N],size[N],fr[N],la[N],fa[N],son[N],top[N];
inline void dfs(int u){
    dep[u]=dep[fa[u]]+1,size[u]=1,a[fr[u]=++idx]=u;
    cross(i,u){
        int v=to[i];if(v==fa[u]) continue;fa[v]=u,dfs(v),size[u]+=size[v];
        if(!son[u]||size[v]>size[son[u]]) son[u]=v;
    }
    la[u]=idx;
}
inline void dfs(int u,int tp){
    top[u]=tp;if(!son[u]) return;dfs(son[u],tp);
    cross(i,u){int v=to[i];if(v==son[u]||v==fa[u]) continue;dfs(v,v);}
}
struct Tree{int ls,rs,sum;}T[N*20];
int Cnt=0,rt[N];
#define mid (l+r>>1)
inline void insert(int &u,int tu,int l,int r,int x){
    T[u=++Cnt]=T[tu],T[u].sum++;if(l==r) return;
    if(x<=mid) insert(T[u].ls,T[tu].ls,l,mid,x);
    else insert(T[u].rs,T[tu].rs,mid+1,r,x);
}
inline int query(int L,int R,int l,int r,LL k){
    if(l==r) return l;int s=T[T[R].ls].sum-T[T[L].ls].sum;
    if(k<=s) return query(T[L].ls,T[R].ls,l,mid,k);
    else return query(T[L].rs,T[R].rs,mid+1,r,k-s);
}
inline int dis(int u,int v){
    int U=u,V=v;
    while(top[u]!=top[v]){if(dep[top[u]]<dep[top[v]]) swap(u,v);u=fa[top[u]];}
    return dep[U]+dep[V]-dep[dep[u]<dep[v]?u:v]*2;
}
inline int find(int l,int r,LL x){
    int ans=0,Mid;
    while(l<=r) if(S[Mid=mid]<=x) l=Mid+1,ans=Mid;else r=Mid-1;
    return ans;
}
int Dep[N],Fa[N][25];LL Sum[N];
inline void Dfs(int u){
    for(int i=1;(1<<i)<=Dep[u];i++) Fa[u][i]=Fa[Fa[u][i-1]][i-1];
    cross(i,u){
        int v=to[i],w=tw[i];if(v==Fa[u][0]) continue;
        Fa[v][0]=u,Sum[v]=Sum[u]+w,Dep[v]=Dep[u]+1;Dfs(v);
    }
}
inline LL Dis(LL u,LL v){
    int x=find(1,cnt,u),y=find(1,cnt,v);
    u=query(rt[fr[A[x]]-1],rt[la[A[x]]],1,n,u-S[x]+1);
    v=query(rt[fr[A[y]]-1],rt[la[A[y]]],1,n,v-S[y]+1);
    if(x==y) return dis(u,v);if(Dep[x]>Dep[y]) swap(x,y),swap(u,v);
    int X=x,Y=y;for(int d=Dep[y]-Dep[x],i=0;d;d>>=1,i++) if(d&1) y=Fa[y][i];
    if(x==y){
        x=X,y=Y; for(int d=Dep[y]-Dep[x]-1,i=0;d;d>>=1,i++) if(d&1) y=Fa[y][i];
        return dis(v,A[Y])+Sum[Y]-Sum[y]+1+dis(u,B[y]);
    }
    DFor(i,20,0) if(Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return dis(u,A[X])+dis(v,A[Y])+Sum[X]-Sum[x]+Sum[Y]-Sum[y]+2+dis(B[x],B[y]);
}
int main(){
    n=read(),m=read(),q=read();
    For(i,1,n-1){int x=read(),y=read();addedge(x,y,0),addedge(y,x,0);}
    dfs(1),dfs(1,1);For(i,1,n) insert(rt[i],rt[i-1],1,n,a[i]);
    S[1]=1,A[1]=1,cnt=1,edge=0;memset(hd,0,sizeof hd);
    while(m--){
        A[++cnt]=read(),B[cnt]=read();int t=find(1,cnt-1,B[cnt]);
        B[cnt]=query(rt[fr[A[t]]-1],rt[la[A[t]]],1,n,B[cnt]-S[t]+1);
        S[cnt]=S[cnt-1]+size[A[cnt-1]];
        int W=dis(A[t],B[cnt])+1;addedge(t,cnt,W),addedge(cnt,t,W);
    }
    Dfs(1);while(q--) write(Dis(read(),read())),putchar('\n');
    return 0;
}
