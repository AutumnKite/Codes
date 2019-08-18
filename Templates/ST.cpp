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
#define N 100005
int n,m,f[N][20],Log[N];
int main(){
    n=read(),m=read();
    Log[1]=0;
    For(i,2,n) Log[i]=Log[i>>1]+1;
    For(i,1,n) f[i][0]=read();
    For(j,1,20){
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=Max(f[i][j-1],f[i+(1<<j-1)][j-1]);
    }
    For(i,1,m){
        int l=read(),r=read();
        write(Max(f[l][Log[r-l+1]],f[r-(1<<Log[r-l+1])+1][Log[r-l+1]]));
        putchar('\n');
    }
    return 0;
}
