#include<stdio.h>

int main(){
    int n,i,j;//int x,y;
    int arr[100][100]={0};
    scanf("%d",&n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i%2==0){
                arr[i][j]=i*n+(j+1);
            }
            else if(i%2==1){
                arr[i][j]=i*n+n-j;
            }
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%2d ",arr[i][j]);
        }
        printf("\n");
    }
}
