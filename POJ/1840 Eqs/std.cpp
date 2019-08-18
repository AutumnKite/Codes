#include <cstdio>
#include <map>
using namespace std;
int a1,a2,a3,a4,a5,ans,cub[105],MAX,MIN;
map<int,int> H;
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int main(){
	scanf("%d%d%d%d%d",&a1,&a2,&a3,&a4,&a5);
	for (register int i=-50;i<=50;++i) cub[i+50]=i*i*i;
	for (register int x1=0;x1<=100;++x1)
		for (register int x2=0;x2<=100;++x2){
			register int t=a1*cub[x1]+a2*cub[x2];
			if (x1!=50&&x2!=50) ++H[t],MAX=max(MAX,t),MIN=min(MIN,t);
		}
	for (register int x3=0;x3<=100;++x3)
		for (register int x4=0;x4<=100;++x4)
			for (register int x5=0;x5<=100;++x5){
				register int t=-a3*cub[x3]-a4*cub[x4]-a5*cub[x5];
				if (x3==50||x4==50||x5==50||t<MIN||t>MAX) continue;
				if (H.count(t)) ans+=H[t];
			}
	printf("%d",ans);
}
