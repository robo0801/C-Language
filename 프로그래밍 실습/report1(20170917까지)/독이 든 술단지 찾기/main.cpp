#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
int a[100000];  //독이 든 술단지는 1, 없으면 0을 넣는다.
int b[100];     //각 신하의 상태 표시
using namespace std;

int binum(int x) //이진수 변환
{
    int i=0;     // 필요한 최소 신하 수
    while(x!=0)  //0이 아닐때까지
    {
        i++;    //i는 이진수 자릿수
        x/=2;   //2로 나눈다.
    }
    return i;
}

void drink(int n, int num)  //술 마시기
{
    int i, j, t, k;
    for(i=1; i<=n; i++)
    {
        t=i;                    //t는 술단지 번호
        j=1;                    //j는 신하 번호
        while(t!=0)                 //각 술단지마다 이진수 변환
        {
            if(t%2) b[j]+=a[i];  //각 술단지의 자리수에 1이 있는 사람만 마시기
            j++;
            t/=2;
        }
    }
}

void solve(int n, int num)//답 구하는 함수
{
    int i, j=0, ans=0;
    printf("구한 정답: ");
    for(i=1; i<=num; i++)
    {
        if(b[i]) ans+=pow(2, i-1);  //독이 든 술을 마신 신하는 자신의 이진수 자리만큼 더해준다.
    }
    printf("%d\n", ans);
}

int main()
{
    int n, i, t, num;
    scanf("%d", &n);        //총 술단지 출력
    srand(time(NULL));
    t=rand()%n+1;           //랜덤함수로 독이 든 술단지 고르기
    a[t]=1;                 //독이 든 술단지 표시

    num=binum(n);           //신하 수 구하기
    drink(n, num);          //마시기

    printf("죽은 신하:");
    for(i=1; i<=num; i++)
        if(b[i]) printf("%d ", i);//독 든 술을 먹은 신하는 0이 아님

    printf("\n");
    solve(n, num);
    printf("실제 정답: %d", t);
    return 0;
}
