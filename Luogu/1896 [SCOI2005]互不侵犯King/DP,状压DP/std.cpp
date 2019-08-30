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
#define N 10
int n,m,a[1<<N],b[1<<N];
LL f[N][1<<N][N*N],ans;
inline int count(int x){
    int s=0;
    for(;x;x-=x&-x) s++;
    return s;
}
int main(){
//#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#else
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    n=read(),m=read();
    For(i,0,(1<<n)-1) f[1][i][a[i]=count(i)]=b[i]=(i&(i>>1))?0:1;
    For(i,2,n) For(j,0,(1<<n)-1) For(k,a[j],m){
        f[i][j][k]=0;
        if(b[j]){
            For(l,0,(1<<n)-1)
                if(!(j<<1&l)&&!(j&l)&&!(j>>1&l)) f[i][j][k]+=f[i-1][l][k-a[j]];
        }
    }
    For(i,0,(1<<n)-1) ans+=f[n][i][m];
    write(ans);
    return 0;
}
