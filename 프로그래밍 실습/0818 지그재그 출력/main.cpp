
#include<stdio.h>

int main(){
    int n,i,j;int x,y;
    int arr[100][100]={0};
    int ch;
    //scanf("%d",&n);
    scanf("%d %d",&x,&y);
    printf("가로는 1, 세로는 2: ");
    scanf("%d",&ch);

    if(ch == 1){
        for(i=0;i<x;i++){
            for(j=0;j<y;j++){
                if(i%2==0){
                    arr[i][j]=i*y+(j+1);
                }
                else if(i%2==1){
                    arr[i][j]=(i+1)*y-j;
                }
            }
            //printf("\n");
        }
        for(i=0;i<x;i++){
            for(j=0;j<y;j++){
                printf("%3d ",arr[i][j]);
            }
            printf("\n");
        }
    }
    if(ch == 2){
        for(i=0;i<x;i++){
            for(j=0;j<y;j++){
                if(i%2==0){
                    arr[j][i]=i*y+(j+1);
                }
                else if(i%2==1){
                    arr[j][i]=(i+1)*y-j;
                }
            }
            //printf("\n");
        }
        for(i=0;i<y;i++){
            for(j=0;j<x;j++){
                printf("%3d ",arr[i][j]);
            }
            printf("\n");
        }
    }


}

/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, i, j;
    scanf("%d%d",&n,&m);
    int arr[n][m];
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if((i%2)==0)
                arr[i][j]=m*i+j+1;
            else
                arr[i][j]=m*(i+1)-j;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%3d ",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
*/
