#include <cstdio>
#define For(i,a,b) for(register int i=(int)(a);i<=(int)(b);++i)
#define cross(i,a) for(register int i=hd[a];i;i=pr[i])
inline int Min(int a,int b){return a<b?a:b;}
const int N=10005,M=200005;
int n,m,ans;
int edge,to[M],pr[M],hd[N];
int col[N],sum[3];
inline void addedge(int u,int v){
    to[++edge]=v,pr[edge]=hd[u],hd[u]=edge;
}
inline bool dfs(int u,int c){
    if(col[u]) return col[u]==c?1:0;
    sum[col[u]=c]++;
    bool bo=1;
    cross(i,u) if(!dfs(to[i],3-c)) bo=0;
    return bo;
}
int main(){
    scanf("%d%d",&n,&m);
    For(i,1,m){
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y),addedge(y,x);
    }
    For(i,1,n) if(!col[i]){
        sum[1]=sum[2]=0;
        if(!dfs(i,1)) return printf("Impossible"),0;
        ans+=Min(sum[1],sum[2]);
    }
    return printf("%d",ans),0;
}
