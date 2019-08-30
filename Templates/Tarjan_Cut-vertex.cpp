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
#define N 100105
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
int n,m,cnt,hd[N],pr[N<<1],to[N<<1],idx,dfn[N],low[N],ans,cut[N];
void add(int u,int v){
    to[++cnt]=v,pr[cnt]=hd[u],hd[u]=cnt;
}
void tarjan(int u,int fa){
    int sum=0;dfn[u]=low[u]=++idx;
    cross(i,u){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v,fa),low[u]=Min(low[u],low[v]),sum++;
            if(low[v]>=dfn[u]&&u!=fa) cut[u]=1;
        }
        else low[u]=Min(low[u],dfn[v]);
    }
    if(u==fa&&sum>=2) cut[u]=1;
}
int main(){
    n=read(),m=read();
    For(i,1,m){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    For(i,1,n) if(!dfn[i]) tarjan(i,i);
    For(i,1,n) ans+=cut[i];
    write(ans),putchar('\n');
    For(i,1,n) if(cut[i]) write(i),putchar(' ');
    return 0;
}
