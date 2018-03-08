#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct StackRecord {
    int Top;
    char Stack[MAX] ={};
}stackType;

//���� �ʱ�ȭ
void init_stack(stackType* Sptr) { Sptr->Top=-1; }

// �� �ֱ�
double push(stackType* Sptr, char Item) {
    if (Sptr->Top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }
    Sptr->Stack[++(Sptr->Top)] = Item;
    return Item;
}

// �� ����
char pop(stackType* Sptr) {
    if (Sptr->Top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return Sptr->Stack[(Sptr->Top)--];
}

// ���� ���
void print_stack(stackType* Sptr){
    int i;
    for (i = Sptr->Top; i >= 0; i--){
        printf("%c ",Sptr->Stack[i]);
    }
}

// ������ TOP�� ���� �����´�.
char get_stack_top(stackType* Sptr){
    return (Sptr->Top < 0) ? -1 : Sptr->Stack[Sptr->Top];
}

// ������ ����ִ��� �˻�
int is_stack_empty(stackType* Sptr){
    return (Sptr->Top < 0);
}

int main() {
    char str[MAX] = {};
    stackType InItem; init_stack(&InItem);
    stackType OutItem; init_stack(&OutItem);
    printf("�����(Y) ������(R) ���(W) ��������(E) ���ٷ� �Է����ּ���.:");
    fgets (str, MAX, stdin);
    for(int i=0;i<strlen(str);i++){
        if(str[i] == 'Y' || str[i] == 'R' || str[i] == 'W') {
            push(&InItem,str[i]);

        }
        else if(str[i] == 'E'){
            break;
        }
    }
    char c;
    while(!is_stack_empty(&InItem)) {
        c=pop(&InItem);
        if(c == 'Y'){
            continue;
        }
        else if(c == 'R' || c == 'W') {
            push(&OutItem,c);
        }
    }
    print_stack(&OutItem);
    printf("\n");
}
