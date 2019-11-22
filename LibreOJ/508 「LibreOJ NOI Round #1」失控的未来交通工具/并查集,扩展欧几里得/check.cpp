#include <cstdio>
#include <cstdlib>
int main(){
	for (register int i = 1; ; ++i){
        printf("The result of No. %d Case is: ", i);
        system("./gen > data.in");
        system("./std < data.in > std.out");
        system("./bf < data.in > bf.out");
        if (system("diff std.out bf.out")){
            printf("Wrong Answer\n");
            return 0;
        }
        else printf("Accepted\n");
    }
    return 0;
}