// #include<bits/stdc++.h> 
// #define ll long long
// #define For(i,j,k)	for(int i=j;i<=k;++i)
// #define Dow(i,j,k)	for(int i=k;i>=j;--i)
// #define local freopen("in.in","r",stdin);
// #define anss(x,y)  ((x-1))*m+(y)
// #define pb push_back
// using namespace std;
// inline char gc(){
//     static char buf[100000],*p1=buf,*p2=buf;
//     return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
// }
// #define gc getchar
// inline ll read()
// {
// 	ll t=0,f=1;char anss=gc();
// 	while(!isdigit(anss))  {if(anss=='-') f=-1;anss=gc();}
// 	while(isdigit(anss))   t=t*10+anss-'0',anss=gc();
// 	return t*f;
// }
// inline void write(ll x){if(x<0) {putchar('-');write(-x);return;}if(x>=10)    write(x/10);putchar(x%10+'0');}
// inline void writeln(ll x){write(x);puts("");}
// inline void write_p(ll x){write(x);putchar(' ');}

// const int N=705;
// int n,a[N],pre[N][N],fl[N][N],fr[N][N];
// bool flag;
// inline int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
// int main()
// {
// 	n=read();
// 	For(i,1,n)	a[i]=read();
// 	For(i,1,n)	For(j,i+1,n)	pre[i][j]=(gcd(a[i],a[j])>1),pre[j][i]=pre[i][j];
// 	For(i,1,n)	fl[i][i]=fr[i][i]=1;
// 	For(len,1,n)
// 	{
// 		For(l,1,n-len+1)
// 		{
			
// 			int r=l+len-1;
// 			For(k,l,r)
// 			{
// 				if((!fl[k][l])||(!fr[k][r]))	continue;
// 				if(!flag)	if(len==n)	puts("Yes"),flag=1;
// 				if(pre[l-1][k])	fr[l-1][r]=1;if(pre[k][r+1])	fl[r+1][l]=1;
// 			}
// 		}
// 	}
// 	if(!flag)	puts("No");
// }
#include <cstdio>
#define N 705
int n, a[N], can[N][N], dp[2][N][N];
int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i < n; ++i)
		for (register int j = i + 1; j <= n; ++j)
			can[i][j] = gcd(a[i], a[j]) > 1, can[j][i] = can[i][j];
	for (register int i = 1; i <= n; ++i) dp[0][i][i] = dp[1][i][i] = 1;
	for (register int l = 1; l <= n; ++l)
		for (register int i = 1, j; (j = i + l - 1) <= n; ++i)
			for (register int k = i; k <= j; ++k){
				if (!dp[0][k][i] || !dp[1][k][j]) continue;
				if (l == n) return printf("Yes"), 0;
				if (can[i - 1][k]) dp[1][i - 1][j] = 1;
				if (can[k][j + 1]) dp[0][j + 1][i] = 1;
			}
	printf("No");
}