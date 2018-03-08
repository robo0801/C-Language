#include<stdio.h>
/*

8
1 3 -1 -3 5 3 6 7
3

최대값 7
*/

int main(){
    int w=0,len=0,Max = -10000;
    int a[100]={0};
    printf("창 길이를 입력하세요. :");scanf("%d",&len);
    printf("창 배열을 입력하세요: ");
    for(int i=1;i<=len;i++){ scanf("%d",&a[i]);  } //창문 배열 값 입력 받기
    printf("구간을 입력하세요. :");scanf("%d",&w);  //구간 입력
    for(int i=1;i<=len-w+1;i++){    //구간 횟수 만큼 반복하기
        Max = -10000;       // 최대값 변수
        for(int j=1;j<=len;j++){  //구간 배열 출력
            if(j == i){ printf("[%d ",a[j]); }
            else if (j == i+w-1){ printf("%d] ",a[j]); }
            else{ printf("%d ",a[j]); }
        }
        for(int j=i;j<i+w;j++){   // 구간에서 최대값 을 찾기 위함
            if(a[j]>=Max){ Max = a[j]; }//최대값
        } printf(": %d\n",Max);
    }
}
