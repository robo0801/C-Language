#include <stdio.h>
#include <windows.h>

int a[100][100];//�������
int path[10000];//��ΰ� ���� �迭
int n, l, k;

void output()//��� ��� �Լ�
{
    printf("���: ");
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
            if(a[path[num]][n+1]==-1)//����� ���� ������ Ȧ���� ���� ���� ��
            {
                int sum=0;
                for(int j=1;j<=n;j++)
                    sum+=a[path[num]][j];
                if(sum==1)//���� ���� ������ �ϳ��̸� �ٽ� ���� �� �����Ƿ� �Ұ���
                {
                    a[path[num-1]][i]++;
                    a[i][path[num-1]]++;
                    return;
                }
            }
            a[path[num]][i]--;//������ �� ����
            a[i][path[num]]--;//������ �� ����
            path[++num]=i;//������ ���� ��ο� �߰�
            reculsion(num);
        }
    }
}

void allevenpath()
{
    int i, j;
    for(i=1;i<=n;i++)//������ ã��
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
            a[path[k]][i]--;//������ �� ����
            a[i][path[k]]--;//������ �� ����
            path[++k]=i;//������ ���� ��ο� �߰�
        }
    }

    output();
}

void oddexistpath()
{
    printf("��������� �ǵ��ƿ� ���� ������ �Ѻױ׸���� �����մϴ�.\n");
    int i, j, cnt, sum=0;
    for(i=1;i<=n;i++)
    {
        cnt=0;
        for(j=1;j<=n;j++)
            cnt+=a[i][j];
        if(cnt%2==1)//����� ���� ������ Ȧ���� �� ã��
            a[i][n+1]=-1;
    }

    for(i=1;i<=n;i++)//������ ã��
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
        if(cnt2>2)//�Ѻױ׸��� ���ɿ��� Ȯ��
        {
            printf("�Ѻױ׸��⸦ �� �� �����ϴ�.\n");
            exit(1);
        }
    }

    if(cnt2==0)//��� ���� �̾��� ���� ������ ¦�� �� ��
    {
        allevenpath();
        printf("1");
    }
    else//Ȧ���� ���� ������ ��
    {
        oddexistpath();
        printf("%d", num);
    }
}

int main()
{
    int i, j, x, y;
    printf("���� ������ ����� ���� ������ �Է��Ͻÿ�.\n");
    scanf("%d %d", &n, &l);
    printf("����Ǿ� �ִ� �� ���� a b�������� �Է��Ͻÿ�.\nex)3 4->�� 3�� �� 4�� ����Ǿ� ����.\n");
    for(i=1;i<=l;i++)//������� ����
    {
        scanf("%d %d", &x, &y);
        a[x][y]++;
        a[y][x]++;
    }

    check();
}
