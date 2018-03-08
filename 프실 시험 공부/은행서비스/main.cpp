#include <stdio.h>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef struct _info{
    int name, ct, st;   //ct는 온시간,  st는 걸리는 시간
}info;

bool comp(info a, info b)
{
    return a.ct<b.ct;
}

queue <info> q;
int chk[100];
info arr[100];

int main()
{
    int t, timer, max_st, cus, i=0, j, r;
    int total=0, next, sc=0;
    double a, c;
    srand(time(NULL));
    timer=time(NULL);

    scanf("%d %lf %d", &t, &a, &max_st);        //t는 총시간, a는 평균 고객수, max_st는 최대 서비스 시간

    c=t*a;
    cus=(int)(c+0.5);       //총 고객 수

    //printf("총 고객%d\n", cus);

    while(i<cus)            //랜덤함수로 오는시간, 서비스 시간 돌리기
    {
        arr[i].name=i;
        r=rand()%t+1;
        if(chk[r]) continue;    //같은 시간에 오는 것 방지
        else
        {
            arr[i].ct=r;
            chk[r]=1;
            arr[i].st=rand()%max_st+1;
            i++;
        }
    }

    sort(arr, arr+cus, comp);   //오는 시간 순서대로 정렬
    /*
    for(i=0; i<cus; i++)
        printf("%d %d %d\n", arr[i].name, arr[i].ct, arr[i].st);
    */
    j=0;        //고객 수
    for(i=1; i<=t; i++) //i는 시간
    {
        printf("\n현재시각=%d\n", i);
        if(arr[j].ct==i)        //현재 시간과 들어오는 시간이 같으면
        {
            printf("고객 %d이 %d분에 들어옵니다. 서비스 시간은 %d분입니다.\n", arr[j].name, i, arr[j].st);
            if(q.empty())       //현재 아무도 대기중이지 않으면 들여보내기
            {
                printf("고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n", arr[j].name, i, 0);
                next=i+arr[j].st;   //next는 다음 손님이 서비스를 받을 수 있는 시간
                sc++;               //서비스 받은 손님 추가
            }
            q.push(arr[j]);         //큐에 집어넣기
            j++;                    //다음 사람 확인
        }
        if(i==next)                 //서비스 시간이 끝낫으면
        {
            q.pop();                //큐에서 빼기
            if(!q.empty())          //바로 서비스를 받을 수 있는 사람이 있으면
            {
                printf("고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n", q.front().name, i, i-q.front().ct);
                sc++;               //서비스 받은 손님 추가
                total+=i-q.front().ct;//기다린 시간 추가
                next=i+q.front().st;
            }
        }
    }

    printf("\n\n서비스 받은 고객 수 = %d\n", sc);
    printf("전체 대기 시간 = %d\n", total);
    printf("1인당 평균 대기 시간 = %lf\n", (double)total/sc);
    printf("아직 대기중인 고객수 = %d", cus-sc);
    return 0;
}
