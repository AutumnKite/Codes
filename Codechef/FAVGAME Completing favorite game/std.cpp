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
#define N 1005
#define mp make_pair
typedef pair<int,int> D;
int T,n,h,a[N];
vector<int>E[N];
D Dp[25][N];
inline void DP(int u){
    D dp[25][1025];int n=E[u].size();
    For(i,0,n-1) DP(E[u][i]);
    For(i,0,h) For(j,0,(1<<n)-1) dp[i][j]=mp(N,h);
    for(int p=0;p+a[u]<=h;p++) dp[p][0]=mp(0,p+a[u]);
    for(int p=h-a[u]+1;p<=h;p++) dp[p][0]=mp(1,a[u]);
    For(i,0,(1<<n)-1) For(j,0,n-1) if(!(i&1<<j)) For(p,0,h){
        D& a=dp[p][i];
        D& b=dp[p][i|1<<j];
        D& c=Dp[a.second][E[u][j]];
        b=min(b,mp(a.first+c.first,c.second));
    }
	For(p,0,h) Dp[p][u]=dp[p][(1<<n)-1];
}
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    T=read();
    while(T--){
        n=read(),h=read();
        For(i,1,n) a[i]=read();
        For(i,1,n){
            E[i].clear();
            int m=read();
            For(j,1,m){
                int x=read();
                E[i].push_back(x);
            }
        }
        DP(1);
        write(Dp[0][1].first+(Dp[0][1].second?1:0)),putchar('\n');
    }
    return 0;
}
