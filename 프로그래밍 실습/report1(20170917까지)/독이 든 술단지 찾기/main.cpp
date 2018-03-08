#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
int a[100000];  //���� �� �������� 1, ������ 0�� �ִ´�.
int b[100];     //�� ������ ���� ǥ��
using namespace std;

int binum(int x) //������ ��ȯ
{
    int i=0;     // �ʿ��� �ּ� ���� ��
    while(x!=0)  //0�� �ƴҶ�����
    {
        i++;    //i�� ������ �ڸ���
        x/=2;   //2�� ������.
    }
    return i;
}

void drink(int n, int num)  //�� ���ñ�
{
    int i, j, t, k;
    for(i=1; i<=n; i++)
    {
        t=i;                    //t�� ������ ��ȣ
        j=1;                    //j�� ���� ��ȣ
        while(t!=0)                 //�� ���������� ������ ��ȯ
        {
            if(t%2) b[j]+=a[i];  //�� �������� �ڸ����� 1�� �ִ� ����� ���ñ�
            j++;
            t/=2;
        }
    }
}

void solve(int n, int num)//�� ���ϴ� �Լ�
{
    int i, j=0, ans=0;
    printf("���� ����: ");
    for(i=1; i<=num; i++)
    {
        if(b[i]) ans+=pow(2, i-1);  //���� �� ���� ���� ���ϴ� �ڽ��� ������ �ڸ���ŭ �����ش�.
    }
    printf("%d\n", ans);
}

int main()
{
    int n, i, t, num;
    scanf("%d", &n);        //�� ������ ���
    srand(time(NULL));
    t=rand()%n+1;           //�����Լ��� ���� �� ������ ����
    a[t]=1;                 //���� �� ������ ǥ��

    num=binum(n);           //���� �� ���ϱ�
    drink(n, num);          //���ñ�

    printf("���� ����:");
    for(i=1; i<=num; i++)
        if(b[i]) printf("%d ", i);//�� �� ���� ���� ���ϴ� 0�� �ƴ�

    printf("\n");
    solve(n, num);
    printf("���� ����: %d", t);
    return 0;
}
