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
#define N 14
#define INF 1000000000
int n,m,g[N][N],f[N][N][1<<N];
inline int dp(int i,int j,int k){
    if(~f[i][j][k]) return f[i][j][k];
    if(!k) return 0;
    int ans=INF;
    for(int s=(k-1)&k;s;s=(s-1)&k) ans=Min(ans,dp(i,j,s)+dp(i,j,k^s));
    For(l,1,n) if(k&(1<<l-1)&&~g[i][l]) ans=Min(ans,dp(l,j+1,k^(1<<l-1))+g[i][l]*j);
    //printf("f[%d][%d][%d]=%d\n",i,j,k,ans);
    return f[i][j][k]=ans;
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    memset(g,-1,sizeof g);
    For(i,1,m){
        int x=read(),y=read(),z=read();
        if(z<g[x][y]||g[x][y]==-1) g[x][y]=g[y][x]=z;
    }
    memset(f,-1,sizeof f);
    int ans=INF;
    For(i,1,n) ans=Min(ans,dp(i,1,((1<<n)-1)^(1<<i-1)));
    write(ans);
    return 0;
}

