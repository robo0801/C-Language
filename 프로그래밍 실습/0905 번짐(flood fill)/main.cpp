#include<stdio.h>

/*

5
-1 -1 -1 -1 -1
0 0 0 0 0
-1 -1 -1 -1 -1
0 0 0 0 0
0 0 0 0 0
2 2


*/
int n,fl[101][101];
int di[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

void f(int x,int y){
    if(fl[x][y] != 0) return;
    else if(x<=0 || x>n || y<=0 || y>n) return;
    fl[x][y]=2;
    for(int i=0;i<4;i++){
        f(x+di[i][0],y+di[i][1]);
    }
}

int main(){
    int i,j,x,y;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&fl[i][j]);
        }
    }
    printf("시작할 지점을 입력해주세요: x y\n");
    scanf("%d %d",&x,&y);
    f(x,y);

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            printf("%d ",fl[i][j]);
        }
        printf("\n");
    }
}
