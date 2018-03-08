#include<stdio.h>

int main(){
    int arr[26][26]={},a[26][26]={};
    int i,j,k,cnt=0;
    int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

    for(i=1;i<=25;i++){
        for(j=1;j<=25;j++){
            scanf("%d",&arr[i][j]);
            a[i][j]=arr[i][j];
        }
    }

    for(i=1;i<=25;i++){
        for(j=1;j<=25;j++){
            cnt=0;
            for(k=0;k<8;k++){
                if(1<=i+d[k][0] && i+d[k][0] <=25 && 1<=j+d[k][1] && j+d[k][1] <= 25){
                    if(arr[i+d[k][0]][j+d[k][1]]==1){
                        cnt++;
                    }
                }
            }
            if(arr[i][j]==0 && cnt == 3){
                a[i][j]=1;
            }
            if(arr[i][j]==1){
                if(4<=cnt || cnt<=1){
                    a[i][j]=0;
                }
                if(cnt == 2 || cnt == 3){
                    a[i][j]=1;
                }
            }
        }
    }
    //printf("\n");
    for(i=1;i<=25;i++){
        for(j=1;j<=25;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}

/*
#include <stdio.h>

int a[27][27], b[27][27], i, j;

int main()
{
    for(i = 1; i <= 25; i++)
        for(j = 1 ;j <= 25; j++)
        {
            scanf("%d", &a[i][j]);
            b[i][j] = 0;
        }

    for(i = 1; i <= 25; i++, puts(""))
        for(j = 1; j <= 25; j++)
        {
            b[i][j] = a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j+1] + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1];
            if(a[i][j] == 0)
                b[i][j] = b[i][j] == 3 ? 1 : 0;
            else
                b[i][j] = (b[i][j] >= 4 || b[i][j] <= 1) ? 0 : 1;
            printf("%d ", b[i][j]);
        }
    return 0;
}
*/
