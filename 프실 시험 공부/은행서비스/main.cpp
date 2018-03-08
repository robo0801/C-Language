#include <stdio.h>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef struct _info{
    int name, ct, st;   //ct�� �½ð�,  st�� �ɸ��� �ð�
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

    scanf("%d %lf %d", &t, &a, &max_st);        //t�� �ѽð�, a�� ��� ����, max_st�� �ִ� ���� �ð�

    c=t*a;
    cus=(int)(c+0.5);       //�� �� ��

    //printf("�� ��%d\n", cus);

    while(i<cus)            //�����Լ��� ���½ð�, ���� �ð� ������
    {
        arr[i].name=i;
        r=rand()%t+1;
        if(chk[r]) continue;    //���� �ð��� ���� �� ����
        else
        {
            arr[i].ct=r;
            chk[r]=1;
            arr[i].st=rand()%max_st+1;
            i++;
        }
    }

    sort(arr, arr+cus, comp);   //���� �ð� ������� ����
    /*
    for(i=0; i<cus; i++)
        printf("%d %d %d\n", arr[i].name, arr[i].ct, arr[i].st);
    */
    j=0;        //�� ��
    for(i=1; i<=t; i++) //i�� �ð�
    {
        printf("\n����ð�=%d\n", i);
        if(arr[j].ct==i)        //���� �ð��� ������ �ð��� ������
        {
            printf("�� %d�� %d�п� ���ɴϴ�. ���� �ð��� %d���Դϴ�.\n", arr[j].name, i, arr[j].st);
            if(q.empty())       //���� �ƹ��� ��������� ������ �鿩������
            {
                printf("�� %d�� %d�п� ���񽺸� �����մϴ�. ���ð��� %d���̾����ϴ�.\n", arr[j].name, i, 0);
                next=i+arr[j].st;   //next�� ���� �մ��� ���񽺸� ���� �� �ִ� �ð�
                sc++;               //���� ���� �մ� �߰�
            }
            q.push(arr[j]);         //ť�� ����ֱ�
            j++;                    //���� ��� Ȯ��
        }
        if(i==next)                 //���� �ð��� ��������
        {
            q.pop();                //ť���� ����
            if(!q.empty())          //�ٷ� ���񽺸� ���� �� �ִ� ����� ������
            {
                printf("�� %d�� %d�п� ���񽺸� �����մϴ�. ���ð��� %d���̾����ϴ�.\n", q.front().name, i, i-q.front().ct);
                sc++;               //���� ���� �մ� �߰�
                total+=i-q.front().ct;//��ٸ� �ð� �߰�
                next=i+q.front().st;
            }
        }
    }

    printf("\n\n���� ���� �� �� = %d\n", sc);
    printf("��ü ��� �ð� = %d\n", total);
    printf("1�δ� ��� ��� �ð� = %lf\n", (double)total/sc);
    printf("���� ������� ���� = %d", cus-sc);
    return 0;
}
