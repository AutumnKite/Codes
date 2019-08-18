#include <cstdio>
#include <cctype>
#define For(i,a,b) for(register int i=(int)(a);i<=(int)(b);++i)
#define Fod(i,a,b) for(register int i=(int)(a);i>=(int)(b);--i)
using namespace std;
int n,e[55][55],d[55],s,u,m,ans[3005];
inline void dfs(int u){
    For(v,1,52) e[u][v]?e[u][v]=e[v][u]=0,dfs(v),0:0;
    ans[++m]=u;
}
int main(){
    scanf("%d",&n);
    For(i,1,n){
        char a,b;
        while(!isalpha(a=getchar()));
        b=getchar(),a=isupper(a)?a-64:a-70,b=isupper(b)?b-64:b-70;
        e[a][b]=e[b][a]=1,d[a]++,d[b]++;
    }
    For(i,1,52) d[i]&1?++s,!u?u=i:0:0;
    if(s>2) return printf("No Solution"),0;
    if(!u) For(i,1,52) !u&&d[i]?u=i:0;
    dfs(u);
    Fod(i,m,1) putchar(ans[i]<=26?ans[i]+64:ans[i]+70);
}
