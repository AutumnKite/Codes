#include<bits/stdc++.h>
#define For(i,x,y) for (int i=(x);i<=(y);i++)
#define FOR(i,x,y) for (int i=(x);i<(y);i++)
#define Dow(i,x,y) for (int i=(x);i>=(y);i--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ep emplace_back
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define fil(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
typedef pair<ll,ll> PA;
typedef vector<int> poly;
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while ((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N = 1010;
int n,A,B;
double f[N];
inline double calc(int l,int r){
	return (r-l+1)*(l+r)/2;
}
inline void solve(){
	n=read(),A=read(),B=read();
	f[n]=0;
  double sum=0;
	For(i,0,n-1){
		double l=0,r=1e5;
		For(j,1,40){
			double mid=(l+r)/2;
			double s=0;
			// FOR(a,0,A) FOR(b,0,B){
			// 	s+=min(mid,sum*(A-a)/A*b/B+mid*(A-a)/A);
			// }
			FOR(a,0,A){
				double b=mid*(A-a)/A;
				double k=sum*(A-a)*A/B;
				if (k>0){
					ll Mid=floor((mid-b)/k);
					if (Mid<-1) Mid=-1;
					if (Mid>B-1) Mid=B-1;
					s+=k*calc(0,Mid)+b*(Mid+1);
					s+=(B-1-Mid)*mid;
				} else {
					ll Mid=ceil((mid-b)/k);
					if (Mid<0) Mid=0;
					if (Mid>B) Mid=B;
					s+=k*calc(Mid,B-1)+b*(B-Mid);
					s+=Mid*mid;
				}
			}
			// FOR(a,0,A){
			// 	double b=f[i+1]*a/A+mid*(A-a)/A;
			// 	double k=(f0-mid)*(A-a)/A/B;
			// 	if (k>0){
			// 		ll Mid=floor((mid-b)/k);
			// 		if (Mid<-1) Mid=-1;
			// 		if (Mid>B-1) Mid=B-1;
			// 		s+=k*calc(0,Mid)+b*(Mid+1);
			// 		s+=(B-1-Mid)*mid;
			// 	} else {
			// 		ll Mid=ceil((mid-b)/k);
			// 		if (Mid<0) Mid=0;
			// 		if (Mid>B) Mid=B;
			// 		s+=k*calc(Mid,B-1)+b*(B-Mid);
			// 		s+=Mid*mid;
			// 	}
			// }
			s=s/(A*B);
			s+=1;
			if (mid<s) l=mid;
				else r=mid;
		}
		f[i]=l;
    sum+=f[i];
	}
  printf("%.3lf\n",sum);
}

int main(){
	int T=read();
	while (T--) solve();
}
