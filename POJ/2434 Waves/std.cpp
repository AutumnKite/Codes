#include <cstdio>
#include <algorithm>
using namespace std;
int n,b1,b2,m,ans[10][10];
int num(int x){
	if (x<b1) return 1;
	if (x>b1&&x<b2) return 2;
	if (x>b2) return 3;
	return 0;
}
void work(int x,int y,int t,int c){
	if (t<0) return;
	if (t==0) return -4<=x&&x<=4&&-4<=y&&y<=4?ans[x+4][y+4]+=c:0,(void)0;
	register int k=num(x);
	for (register int i=0,X,Y;i<t;++i){
		X=x-t+i,Y=y+i;
		if (Y>4) break;
		if (k==2) X=x-(t-i)%((b2-b1-1)<<1),X<=b1?X=(b1<<1)-X+1:0,X>=b2?X=(b2<<1)-X-1:0;
		else if (k==3&&X<=b2) X=(b2<<1)-X+1;
		if (-4<=X&&X<=4&&-4<=Y&&Y<=4) ans[X+4][Y+4]+=c;
	}
	for (register int i=0,X,Y;i<t;++i){
		X=x+i,Y=y+t-i;
		if (Y<-4) break;
		if (k==2) X=x+i%((b2-b1-1)<<1),X>=b2?X=(b2<<1)-X-1:0,X<=b1?X=(b1<<1)-X+1:0;
		else if (k==1&&X>=b1) X=(b1<<1)-X-1;
		if (-4<=X&&X<=4&&-4<=Y&&Y<=4) ans[X+4][Y+4]+=c;
	}
	for (register int i=0,X,Y;i<t;++i){
		X=x+t-i,Y=y-i;
		if (Y<-4) break;
		if (k==2) X=x+(t-i)%((b2-b1-1)<<1),X>=b2?X=(b2<<1)-X-1:0,X<=b1?X=(b1<<1)-X+1:0;
		else if (k==1&&X>=b1) X=(b1<<1)-X-1;
		if (-4<=X&&X<=4&&-4<=Y&&Y<=4) ans[X+4][Y+4]+=c;
	}
	for (register int i=0,X,Y;i<t;++i){
		X=x-i,Y=y-t+i;
		if (Y>4) break;
		if (k==2) X=x-i%((b2-b1-1)<<1),X<=b1?X=(b1<<1)-X+1:0,X>=b2?X=(b2<<1)-X-1:0;
		else if (k==3&&X<=b2) X=(b2<<1)-X+1;
		if (-4<=X&&X<=4&&-4<=Y&&Y<=4) ans[X+4][Y+4]+=c;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&b1,&b2,&m);
	if (b1>b2) swap(b1,b2);
	for (register int i=1,x,y,t;i<=n;++i){
		scanf("%d%d%d",&x,&y,&t);
		work(x,y,m-t,1);
		work(x,y,m-t-2,-1);
	}
	for (register int y=4;y>=-4;--y)
		for (register int x=-4;x<=4;++x){
			if (x==b1||x==b2) putchar('X');
			else if (ans[x+4][y+4]>0) putchar('*');
			else if (ans[x+4][y+4]==0) putchar('-');
			else putchar('o');
			if (x==4) putchar('\n');
		}
}
