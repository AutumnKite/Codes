#include <cstdio>
#define N 100005
int n,nx[N],d[N],s[N];
bool vis[N];
inline void del(int u){vis[u]=1,!(--d[nx[u]])?(del(nx[u]),0):0;}
inline int cc(int u,int d){return s[u]=d,s[nx[u]]?d:(s[u]=cc(nx[u],d+1));}
inline int calc(int u){return s[u]?s[u]:(s[u]=calc(nx[u])+1);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",nx+i),++d[nx[i]];
    for(int i=1;i<=n;++i) if(!d[i]&&!vis[i]) del(i);
    for(int i=1;i<=n;++i) if(d[i]&&!s[i]) cc(i,1);
    for(int i=1;i<=n;++i) if(!d[i]&&!s[i]) calc(i);
    for(int i=1;i<=n;++i) printf("%d\n",s[i]);
}
