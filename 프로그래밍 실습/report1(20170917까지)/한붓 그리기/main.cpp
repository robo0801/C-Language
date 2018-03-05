#include <stdio.h>
#include <windows.h>

int a[100][100];//인접행렬
int path[10000];//경로가 담기는 배열
int n, l, k;

void output()//경로 출력 함수
{
    printf("경로: ");
    for(int i=0;;i++)
    {
        if(path[i]==0)
            break;
        printf("%d ", path[i]);
    }
}

void reculsion(int num)
{
    for(int i=1;i<=n;i++)
    {
        if(a[path[num]][i]!=0)
        {
            if(a[path[num]][n+1]==-1)//연결된 점의 개수가 홀수인 점을 지날 때
            {
                int sum=0;
                for(int j=1;j<=n;j++)
                    sum+=a[path[num]][j];
                if(sum==1)//남은 선의 개수가 하나이면 다시 나올 수 없으므로 불가능
                {
                    a[path[num-1]][i]++;
                    a[i][path[num-1]]++;
                    return;
                }
            }
            a[path[num]][i]--;//지나간 선 제거
            a[i][path[num]]--;//지나간 선 제거
            path[++num]=i;//도착한 점을 경로에 추가
            reculsion(num);
        }
    }
}

void allevenpath()
{
    int i, j;
    for(i=1;i<=n;i++)//시작점 찾기
    {
        for(j=1;j<=n;j++)
        {
            if(a[i][j]==1)
            {
                path[k]=i;
                a[i][j]--;
                a[j][i]--;
                path[++k]=j;
            }
            if(k==1) break;
        }
        if(k==1) break;
    }

    for(i=1;i<=n;i++)
    {
        if(a[path[k]][i]!=0)
        {
            a[path[k]][i]--;//지나간 선 제거
            a[i][path[k]]--;//지나간 선 제거
            path[++k]=i;//도착한 점을 경로에 추가
        }
    }

    output();
}

void oddexistpath()
{
    printf("출발점으로 되돌아올 수는 없으나 한붓그리기는 가능합니다.\n");
    int i, j, cnt, sum=0;
    for(i=1;i<=n;i++)
    {
        cnt=0;
        for(j=1;j<=n;j++)
            cnt+=a[i][j];
        if(cnt%2==1)//연결된 점의 개수가 홀수인 점 찾기
            a[i][n+1]=-1;
    }

    for(i=1;i<=n;i++)//시작점 찾기
        if(a[i][n+1]==-1)
        {
            path[k]=i;
            break;
        }

    reculsion(k);
    output();
}

void check()
{
    int cnt1, cnt2=0, i, num;
    for(i=1;i<=n;i++)
    {
        cnt1=0;
        for(int j=1;j<=n;j++)
            cnt1+=a[i][j];
        if(cnt1%2!=0)
        {
            cnt2++;
            if(cnt2==2)
                num=i;
        }
        if(cnt2>2)//한붓그리기 가능여부 확인
        {
            printf("한붓그리기를 할 수 없습니다.\n");
            exit(1);
        }
    }

    if(cnt2==0)//모든 점의 이어진 점의 개수가 짝수 일 때
    {
        allevenpath();
        printf("1");
    }
    else//홀수인 점이 존재할 때
    {
        oddexistpath();
        printf("%d", num);
    }
}

int main()
{
    int i, j, x, y;
    printf("점의 개수와 연결된 선의 개수를 입력하시오.\n");
    scanf("%d %d", &n, &l);
    printf("연결되어 있는 두 점을 a b형식으로 입력하시오.\nex)3 4->점 3과 점 4가 연결되어 있음.\n");
    for(i=1;i<=l;i++)//인접행렬 형성
    {
        scanf("%d %d", &x, &y);
        a[x][y]++;
        a[y][x]++;
    }

    check();
}
