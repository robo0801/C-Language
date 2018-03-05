#include<stdio.h>

int a[11][11],r,c,i,j;

int main(){
    for(i=1;i<=9;i++){
        for(j=1;j<=9;j++){
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d %d",&r,&c);

    if(a[r][c]==1){
        printf("-1");
    }
    else{
        int k = a[r-1][c-1] + a[r-1][c] + a[r-1][c+1] + a[r][c-1] + a[r][c+1] + a[r+1][c-1] + a[r+1][c] + a[r+1][c+1];
        printf("%d",k);
    }
}
