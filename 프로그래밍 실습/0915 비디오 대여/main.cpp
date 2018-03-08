//  http://ehpub.co.kr/c%EC%96%B8%EC%96%B4-%EC%86%8C%EC%8A%A4-%EB%8D%94%EB%AF%B8-%EB%85%B8%EB%93%9C%EC%9E%88%EB%8A%94-%EC%9D%B4%EC%A4%91-%EC%97%B0%EA%B2%B0%EB%A6%AC%EC%8A%A4%ED%8A%B8/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

Node *NewNode(int data) {
    Node *now = (Node *)malloc(sizeof(Node));
    now->data = data;
    now->prev = now->next = NULL;
    return now;
}

typedef struct List//���Ḯ��Ʈ ����
{
    Node *head;
    Node *tail;
    int count;
}List;

void InitList(List *list);//�ʱ�ȭ
void AddData(List *list, int data);//������ �߰�
void Remove(List *list, Node *now);//��� ����
Node *Find(List *list, int data);//��� �˻�(����Ʈ���� �� ó�� �߰��� ��� ��ȯ)
Node *Find2(List *list, Node *seek, int data);//��� �˻�(pos ���� ��忡������ ó�� �߰��� ��� ��ȯ)
void ViewAll(List *list);//��ü ���
void Clear(List *list);//����

int main(void)
{
    int cmd = -1;
    while(cmd == 0){

    }
    //---
    List list;
    {//�ʱ�ȭ �� �߰� �׽�Ʈ�� ���� ���
        InitList(&list);
        AddData(&list, 3); //3
        AddData(&list, 4); //3 4
        AddData(&list, 6); //3 4 6
        AddData(&list, 9); //3 4 6 9
        ViewAll(&list);// 3 4 6 9 ���
    }

    {//�˻��� ���� �׽�Ʈ�� ���� ���
        Node *seek = Find(&list, 4);
        if (seek)
        {
            printf("4�� ������ ��带 ã����\n");
            Remove(&list, seek); //3 6 9
            printf("4�� ������ ��� ���� ��\n");
            ViewAll(&list);// 3 6 9 ���
        }
    }
    Clear(&list);//��ü ����
    printf("��ü ���� ��\n");
    ViewAll(&list);// �ƹ��͵� ������� ����

    return 0;
}

void InitList(List *list)
{
    list->head = NewNode(0);//���� ����Ʈ�� �� �տ� ���� ��� ����
    list->tail = NewNode(0);//���� ����Ʈ�� �� �ڿ� ���� ��� ����
    list->head->next = list->tail;//head�� ������ tail�� ����
    list->tail->prev = list->head;//tail�� ������ head�� ����
    list->count = 0;//������ ������ ������ 0���� ����
}
void AddData(List *list, int data)
{
    //���� ������ ��带 tail�տ� �Ŵ�ϴ�.
    Node *now = NewNode(data);//���ο� ��� ����
    now->prev = list->tail->prev;//now�� prev�� tail �� ���� ����
    now->next = list->tail;//now�� next�� tail�� ����
    list->tail->prev->next = now;//tail�� ���� ����� next�� now�� ����
    list->tail->prev = now;//tail�� prev�� now�� ����
    list->count++;//������ ������ ������ 1 ����
}

void Remove(List *list, Node *now)
{
    now->prev->next = now->next;//���� ����� next�� now�� ���� ���� ����
    now->next->prev = now->prev;//���� ����� prev�� now�� ���� ���� ����
    free(now);//��� �Ҹ�
    list->count--;//������ ��� ������ 1 ����
}

Node *Find(List *list, int data)
{
    //head�� tail�� ���� ����Դϴ�.
    Node *seek = list->head->next;//head�� next���� �˻��մϴ�.
    while (seek != list->tail) //seek�� tail�� �ƴϸ�
    {
        if (seek->data == data)//ã���� ��
        {
            return seek;
        }
        seek = seek->next;//seek�� �������� �̵�
    }
    return NULL;//�� ã���� ��
}

Node *Find2(List *list, Node *seek, int data)
{
    seek = seek->next;//seek ���� ������ �˻��մϴ�.
    while (seek != list->tail) //seek�� tail�� �ƴϸ�
    {
        if (seek->data == data)//ã���� ��
        {
            return seek;
        }
        seek = seek->next;//seek�� �������� �̵�
    }
    return NULL;//�� ã���� ��
}
void ViewAll(List *list)
{
    //head�� tail�� ���� ����Դϴ�.
    Node *seek = list->head->next;//head->next ���� ����մϴ�.
    int i = 0;
    printf("������ ������ ����: %d\n", list->count);

    while (seek != list->tail) //seek�� ���̸�(NULL �� �ƴϸ�)
    {
        i++;
        printf("[%2d]:%-05d ", i, seek->data);

        if (i % 5 == 0)//5�� ����� ��
        {
            printf("\n");//����
        }
        seek = seek->next;//seek�� �������� �̵�
    }
    printf("\n");
}

void Clear(List *list)
{
    //head ���� ��尡 tail�� �ƴ� ������ ����Ʈ���� ����
    Node *seek = list->head->next;
    while (seek != list->tail) //seek�� ���̸�(NULL �� �ƴϸ�)
    {
        Remove(list, seek);
        seek = list->head->next;
    }
}
