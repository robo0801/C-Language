/*
입력 예시
13
1 1 1 1 1 1 1 1 0 1 1 1 1
9

15
1 1 1 0 1 1 1 1 1 1 1 1 1 1 1
4

14
1 1 1 1 0 1 1 1 1 1 1 1 1 1 1
5
*/


//3진 탐색
#include<stdio.h>
#define MAX 100
//들어 온 동전 저장 순서대로 합을 저정
int arr[MAX]={0};

void fi(int s,int f){
    int m1,m2;
    printf("%d %d\n",s,f);
    if((f-s)<=2){ //끝과 끝이 2이하면 return
        printf("%d",((arr[s]>arr[s-1]) > (arr[f]>arr[f-1]) )? f : s );
        return;
    }

    //m1 값 지정 m2 값 지정 배열에서 3분의 1지점 3분의 2지점
    if( (f-s)%3==0 ){ m1=s-1+(f-s)/3; m2=s-1+2*(f-s)/3; }
    else if( (f-s)%3==1 ){ m1=s-1+(f-s)/3+1; m2=s-1+2*(f-s)/3+2; }
    else if( (f-s)%3==2 ){ m1=s-1+(f-s+1)/3; m2=s-1+2*(f-s+1)/3; }
    printf(":%d %d\n",m1,m2);
    // 합 비교 하기 작으면 함수 호출 같으면 비교 안했던 값 함수 호출
    if((arr[m1]-arr[s-1]) > (arr[m2]-arr[m1]) ) {printf(">"); fi(m1+1,m2); }
    else if( (arr[m1]-arr[s-1]) < (arr[m2]-arr[m1]) ) {printf("<"); fi(s,m1); }
    else if( (arr[m1]-arr[s-1]) == (arr[m2]-arr[m1]) ) {printf("="); fi(m2+1,f); }
}

int main(){
    int n,sum=0;

    scanf("%d",&n);
    for(int i=1;i<=n;i++){ //동전 합을 저장
        scanf("%d",&sum);
        arr[i]=arr[i-1]+sum;
    }
    fi(1,n); //재귀 함수 호출 첫번째 값 마지막 값
}
