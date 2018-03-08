#include<stdio.h>
#include<stdlib.h>

//��� ����ü ����
typedef struct ListNode{
    float coef;
    int expo;
    struct ListNode* link; //������� ����ų ����ü
}ListNode;

typedef struct ListHead{ //��� head ����
    ListNode* head;
}ListHead;

// head ����
ListHead* makeLL(void) {
    ListHead* L;
    L = (ListHead*)malloc(sizeof(ListHead));
    L->head = NULL;
    return L;
}

//��� �߰��ϱ� + ����
void addN(ListHead* H, float coef, int expo){ //addNode
    int temp=0,check=0;     //�޾ƿ� ���� ��忡 �ֱ�
    float temc;             //��带 ����� �����Ͽ� �ֱ�
    ListNode* newNode;
    ListNode* p;
    newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->coef = coef;
    newNode->expo = expo;
    newNode->link = NULL;
    if(H->head == NULL){
        H->head = newNode;
        return;
    }
    else {
        p = H->head;
        if((p->expo) < (newNode->expo)){ //�����ϱ�
            //printf("%d %d\n",expo,p->expo);
            temp = p->expo;
            p->expo = newNode->expo;
            newNode->expo = temp;
            temc = p->coef;
            p->coef = newNode->coef;
            newNode->coef = temc;
        }
        while(p->link != NULL){ //�����ϱ�
            p = p->link;
            if((p->expo) < (newNode->expo)){
                printf("%d %d\n",expo,p->expo);
                temp = p->expo;
                p->expo = newNode->expo;
                newNode->expo = temp;
                temc = p->coef;
                p->coef = newNode->coef;
                newNode->coef = temc;
            }
        }
        p->link = newNode;
        return;
    }
}

//�޾ƿ� ��� ���׽� �з� �� ���ϱ�
void addPoly(ListHead* A, ListHead* B, ListHead* C) {
    ListNode* tA = A->head;
    ListNode* tB = B->head;
    float sum;

    while(tA && tB) {
        if(tA->expo == tB->expo){
            sum = tA->coef + tB->coef;
            addN(C,sum,tA->expo);
            tA = tA->link;
            tB = tB->link;
        }
        else if(tA->expo > tB->expo) {
            addN(C, tA->coef, tA->expo);
            tA=tA->link;
        }
        else{
            addN(C, tB->coef, tB->expo);
            tB=tB->link;
        }
    }
    while(tA!=NULL){
        addN(C, tA->coef, tA->expo);
        tA=tA->link;
    }
    while(tB!=NULL){
        addN(C, tB->coef, tB->expo);
        tB=tB->link;
    }
}
/*
void ListSort(ListHead* L) {
    ListNode* temp;
    ListNode* pi= L->head;
    ListNode* pj= L->head;

    for( ; pi->link!=NULL; pi=pi->link){
        for(pj=pi ; pj->link!=NULL; pj=pj->link){
            if(pj->coef > (pj->link)->coef){
                temp = pj->link;
                pj->link = (pj->link)->link;
                (pj->link)->link = pj->link;
            }
        }
    }
}
*/
//����Լ�
void printPoly(ListHead* H) {
    ListNode* p = H->head;
    for(;p;p=p->link){
        printf("%3.0fx^%d", p->coef, p->expo);
    }
}

int main(){
    ListHead *A, *B, *C; //����
    int i,nodecount,coef,expo;

    //A(x) ���׽� �Է�
    A = makeLL();
    printf("A(x)�� ���׽��� ���� ���� �Է����ּ���. :");
    scanf("%d",&nodecount);
    printf("�� ���� ����� ������ ���ʷ� �Է����ּ���. :");
    for(i=0;i<nodecount;i++){
        scanf("%d %d",&coef,&expo);
        addN(A,coef,expo);
    }

    //B(x)���׽� �Է�
    B = makeLL();
    printf("B(x)�� ���׽��� ���� ���� �Է����ּ���. :");
    scanf("%d",&nodecount);
    printf("�� ���� ����� ������ ���ʷ� �Է����ּ���. :");
    for(i=0;i<nodecount;i++){
        scanf("%d %d",&coef,&expo);
        addN(B,coef,expo);
    }
    //�� ���׽� ���
    printf("\n A(x)=");printPoly(A);
    printf("\n B(x)=");printPoly(B);

    C = makeLL();
    addPoly(A, B, C); // ���ϱ�
    printf("\n�����:\n C(x)=");printPoly(C);
}
