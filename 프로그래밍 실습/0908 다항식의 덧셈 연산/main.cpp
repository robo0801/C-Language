#include<stdio.h>
#include<stdlib.h>

//노드 구조체 선언
typedef struct ListNode{
    float coef;
    int expo;
    struct ListNode* link; //다음노드 가르킬 구조체
}ListNode;

typedef struct ListHead{ //노드 head 선언
    ListNode* head;
}ListHead;

// head 생성
ListHead* makeLL(void) {
    ListHead* L;
    L = (ListHead*)malloc(sizeof(ListHead));
    L->head = NULL;
    return L;
}

//노드 추가하기 + 정렬
void addN(ListHead* H, float coef, int expo){ //addNode
    int temp=0,check=0;     //받아온 값을 노드에 넣기
    float temc;             //노드를 만들고 정렬하여 넣기
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
        if((p->expo) < (newNode->expo)){ //정렬하기
            //printf("%d %d\n",expo,p->expo);
            temp = p->expo;
            p->expo = newNode->expo;
            newNode->expo = temp;
            temc = p->coef;
            p->coef = newNode->coef;
            newNode->coef = temc;
        }
        while(p->link != NULL){ //정렬하기
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

//받아온 노드 다항식 분류 후 더하기
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
//출력함수
void printPoly(ListHead* H) {
    ListNode* p = H->head;
    for(;p;p=p->link){
        printf("%3.0fx^%d", p->coef, p->expo);
    }
}

int main(){
    ListHead *A, *B, *C; //생성
    int i,nodecount,coef,expo;

    //A(x) 다항식 입력
    A = makeLL();
    printf("A(x)의 다항식의 항의 수를 입력해주세요. :");
    scanf("%d",&nodecount);
    printf("각 항의 계수와 지수를 차례로 입력해주세요. :");
    for(i=0;i<nodecount;i++){
        scanf("%d %d",&coef,&expo);
        addN(A,coef,expo);
    }

    //B(x)다항식 입력
    B = makeLL();
    printf("B(x)의 다항식의 항의 수를 입력해주세요. :");
    scanf("%d",&nodecount);
    printf("각 항의 계수와 지수를 차례로 입력해주세요. :");
    for(i=0;i<nodecount;i++){
        scanf("%d %d",&coef,&expo);
        addN(B,coef,expo);
    }
    //두 다항식 출력
    printf("\n A(x)=");printPoly(A);
    printf("\n B(x)=");printPoly(B);

    C = makeLL();
    addPoly(A, B, C); // 더하기
    printf("\n결과는:\n C(x)=");printPoly(C);
}
