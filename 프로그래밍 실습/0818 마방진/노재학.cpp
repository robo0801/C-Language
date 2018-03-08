#include<stdio.h>
#include<stdlib.h>

int main(){
    int n=1,arr[100][100]={0};
    int i,j,k=0;
    // 마방진 크기 입력 받기
    while(n!=0){
        printf("마방진 크기 입력하세요. 홀수만 입력 :");
        scanf("%d",&n);
        if(n%2==1) break;

    }
    if(n==0) return 0; // 0 일때는 종료

    //마방진 배열에 수 넣기
    i=1;j=n/2+1;
    while(k!=n*n){
        k++;
        while(1){
            if(arr[i][j]==0){ // 배열이 비었을 때 수 넣기
                arr[i][j]=k;
                break;
            }
            else{ // 만약 배열에 숫자가 있을 때 바로 밑 배열로 장소 이동
                j+=1;
                i+=2;
                if(i>n) i-=n;
                if(j>n) j-=n;
            }
        }
        // 그 다음방으로 이동
        i-=1;j-=1;
        if(i==0) i+=n;
        if(j==0) j+=n;
    }

    // 출력
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            printf("%2d ",arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
