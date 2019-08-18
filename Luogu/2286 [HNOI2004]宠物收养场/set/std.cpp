#include <cstdio>
#include <cctype>
#include <algorithm>
#include <set>
int read(){
	int x=0,f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
int n,tmp;
long long ans;
std::set<long long> T;
long long abs(long long a){return a>0?a:-a;}
int main(){
	n=read();
	T.insert(-1000000000000000000ll);
	T.insert(1000000000000000000ll);
	for (register int i=1;i<=n;++i){
		long long a=read(),b=read();
		if (T.size()==2||a==tmp) tmp=a,T.insert(b);
		else{
			std::set<long long>::iterator x=T.upper_bound(b),y=T.lower_bound(b);
			--x;
			if (abs(*x-b)>abs(*y-b)) std::swap(x,y);
			(ans+=abs(*x-b))%=1000000,T.erase(x);
		}
	}
	printf("%lld",ans);
}
