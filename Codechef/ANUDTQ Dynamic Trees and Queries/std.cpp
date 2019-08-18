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
#define For(i,a,b) for(int i=(int)(a),i_E=(int)(b);i<=i_E;i++)
#define DFor(i,a,b) for(int i=(int)(a),i_E=(int)(b);i>=i_E;i--)
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
#define N 200005
int n,m,cnt,val[N],bol[N],Fa[N];
LL ans=0;
int edge=0,to[N<<1],pr[N<<1],hd[N];
inline void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
int fa[N],idx=0,ds[N],de[N],dt[N];
inline void dfs(int u){
    if(!bol[u]) return;
    dt[ds[u]=++idx]=u;
    cross(i,u){
        int v=to[i];
        if(v==fa[u]) continue;
        fa[v]=u,dfs(v);
    }
    de[u]=idx;
}
struct node{
    LL sum;int lz,len,bo;
}T[N<<3];
inline void up(int u){
    T[u].sum=T[u<<1].sum+T[u<<1|1].sum;
    T[u].len=T[u<<1].len+T[u<<1|1].len;
}
inline void down(int u){
    if(T[u].lz!=0){
        T[u<<1].sum+=1ll*T[u].lz*T[u<<1].len,T[u<<1].lz+=T[u].lz;
        T[u<<1|1].sum+=1ll*T[u].lz*T[u<<1|1].len,T[u<<1|1].lz+=T[u].lz;
        T[u].lz=0;
    }
}
inline void build(int u,int l,int r){
    if(l==r){
        T[u].sum=val[dt[l]],T[u].lz=0,T[u].len=1,T[u].bo=1;
        return;
    }
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    up(u),T[u].lz=0,T[u].bo=1;
}
inline void update(int u,int l,int r,int L,int R,int x){
    if(!T[u].bo) return;
    if(L<=l&&r<=R){
        T[u].sum+=1ll*T[u].len*x,T[u].lz+=x;
        return;
    }
    int mid=(l+r)>>1;down(u);
    if(L<=mid) update(u<<1,l,mid,L,R,x);
    if(R>mid) update(u<<1|1,mid+1,r,L,R,x);
    up(u);
}
inline LL query(int u,int l,int r,int L,int R){
    if(!T[u].bo) return 0;
    if(L<=l&&r<=R) return T[u].sum;
    int mid=(l+r)>>1;LL ans=0;down(u);
    if(L<=mid) ans+=query(u<<1,l,mid,L,R);
    if(R>mid) ans+=query(u<<1|1,mid+1,r,L,R);
    return ans;
}
inline void Delete(int u,int l,int r,int L,int R){
    if(!T[u].bo) return;
    if(L<=l&&r<=R){
        T[u].sum=T[u].lz=T[u].len=T[u].bo=0;
        return;
    }
    int mid=(l+r)>>1;down(u);
    if(L<=mid) Delete(u<<1,l,mid,L,R);
    if(R>mid) Delete(u<<1|1,mid+1,r,L,R);
    up(u);
}
inline void move(int u,int l,int r){
    if(l==r){
        val[dt[l]]=T[u].sum,bol[dt[l]]=T[u].len;
        return;
    }
    int mid=(l+r)>>1;down(u);
    if(!T[u].bo) T[u<<1].len=T[u<<1|1].len=T[u<<1].bo=T[u<<1|1].bo=0;
    move(u<<1,l,mid),move(u<<1|1,mid+1,r);
}
inline void bufdfs(int u,int opt,int x){
    if(!bol[u]) return;
    if(opt==2) val[u]+=x;
    if(opt==3) bol[u]=0;
    if(opt==4) ans+=val[u];
    cross(i,u){
        int v=to[i];
        if(v==fa[u]) continue;
        bufdfs(v,opt,x);
    }
}
int main(){
    n=read();
    For(i,1,n) val[i]=read(),bol[i]=1;
    For(i,1,n-1){
        int x=read()+1,y=read()+1;
        addedge(x,y),addedge(y,x);
    }
    fa[1]=0,idx=0,dfs(1),build(1,1,idx),cnt=n;
    for(m=read();m--;){
        int opt=read();LL x=read()+1+ans;
        if(opt==1){
            val[++cnt]=read(),bol[cnt]=1,Fa[cnt]=x<=n?x:Fa[x];
            addedge(x,cnt),addedge(cnt,x),fa[cnt]=x;
            if(cnt-n==1667) move(1,1,idx),n=cnt,idx=0,dfs(1),build(1,1,idx);
        }
        if(opt==2){
            int y=read();
            if(x<=n){
                update(1,1,idx,ds[x],de[x],y);
                For(i,n+1,cnt) if(ds[Fa[i]]>=ds[x]&&ds[Fa[i]]<=de[x]&&bol[i]) val[i]+=y;
            }
            else bufdfs(x,2,y);
        }
        if(opt==3){
            if(x<=n){
                Delete(1,1,idx,ds[x],de[x]);
                For(i,n+1,cnt) if(ds[Fa[i]]>=ds[x]&&ds[Fa[i]]<=de[x]) bol[i]=0,val[i]=0;
            }
            else bufdfs(x,3,0);
        }
        if(opt==4){
            if(x<=n){
                ans=query(1,1,idx,ds[x],de[x]);
                For(i,n+1,cnt) if(ds[Fa[i]]>=ds[x]&&ds[Fa[i]]<=de[x]&&bol[i]) ans+=val[i];
            }
            else ans=0,bufdfs(x,4,0);
            write(ans),putchar('\n');
        }
    }
    return 0;
}