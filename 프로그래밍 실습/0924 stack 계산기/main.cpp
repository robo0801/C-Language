#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// ���� ����
typedef struct StackRecord {
    int Top;
    double Stack[MAX]={};
}stackType;

//���� �ʱ�ȭ
void init_stack(stackType* Sptr) {
    Sptr->Top=-1;
}

// �� �ֱ�
double push(stackType* Sptr, double Item) {
    if (Sptr->Top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }
    Sptr->Stack[++(Sptr->Top)] = Item;
    return Item;
}

// �� ����
double pop(stackType* Sptr) {
    if (Sptr->Top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return Sptr->Stack[(Sptr->Top)--];
}

// ���� ���
void print_stack(stackType* Sptr){
    int i;
    printf("\n Stack contents : TOP ----> Bottom\n");
    for (i = Sptr->Top; i >= 0; i--){
        printf("%-6f",Sptr->Stack[i]);
    }
}

// ������ TOP�� ���� �����´�.
double get_stack_top(stackType* Sptr){
    return (Sptr->Top < 0) ? -1 : Sptr->Stack[Sptr->Top];
}

// ������ ����ִ��� �˻�
int is_stack_empty(stackType* Sptr){
    return (Sptr->Top < 0);
}

// k �� ���������� �Ǵ��Ѵ�.
int is_operator(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// ����ǥ��� ������ �����Ѱ� üũ
int is_legal(char *s){
    int f = 0;
    while (*s){
        // ó�� ���� �Ѿ��
        while (*s == ' '){
            s++;
        }

        if (is_operator(*s)){
            f--;
        }
        else{
            f++;
            while (*s != ' '){
                s++;
            }
        }
        if (f < 1) break;
        s++;
    }
    return (f == 1);
}

// �������� �켱������ ��ġ�� ��ȯ���ش�.
int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// ����ǥ����� ����ǥ������� ��ȯ
void postfix(stackType* Sptr, char *dst, char *src){
    char c;
    init_stack(Sptr); //�ʱ�ȭ
    while (*src){
        if (*src == '('){ // '(' �̸� �ֱ�
            push(Sptr,*src);
            src++;
        }
        else if (*src == ')'){ // ')' ������ ���� �迭�� ����
            while (get_stack_top(Sptr) != '('){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            pop(Sptr);
            src++;
        }
        else if (is_operator(*src)){ //������ �� ��
                                    // ������ ������� �ʰ� �켱������ �������� �� ���� �迭�� ����
            while (!is_stack_empty(Sptr) &&
                precedence(get_stack_top(Sptr)) >= precedence(*src)){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            push(Sptr,*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9' || *src == '.'){ //�����̸� �ڸ��� Ȯ�� �� �ֱ�
            do{
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9' || *src == '.' );
            *dst++ = ' ';
        }
        else{
            src++;
        }
    }

    while (!is_stack_empty(Sptr)){
        *dst++ = pop(Sptr);
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

// ����ǥ����� ����Ѵ�.
double calc(stackType* Sptr, char *p){
    double i;
    double cnt = 1;

    init_stack(Sptr);
    while (*p){
        if (*p >= '0' && *p <= '9'){
            i = 0;
            do{
                i = i * 10 + *p - '0';
                p++;
            } while (*p >= '0' && *p <= '9');
			cnt =1;
			if( (*p) == '.') {
				p++;
				do{
					i = i * 10 + *p - '0';
					p++;
					cnt = cnt*10;
				} while (*p >= '0' && *p <= '9');
				i=i/cnt;
			}
            push(Sptr,i);
        }
        else if (*p == '+'){
            push(Sptr, pop(Sptr) + pop(Sptr));
            p++;
        }
        else if (*p == '*'){
            push(Sptr, pop(Sptr) * pop(Sptr));
            p++;
        }
        else if (*p == '-'){
            i = pop(Sptr);
            push(Sptr, pop(Sptr) - i);
            p++;
        }
        else if (*p == '/'){
            i = pop(Sptr);
            push(Sptr, pop(Sptr) / i);
            p++;
        }
        else{
            p++;
        }
    }
    return pop(Sptr);
}

int main(){
    double ans;
    char exp[256] = "2*3+6/2-4"; //input example!
    char pf[256];
    stackType formula;

    printf("Input the equation: ");
    scanf("%s",exp);

    postfix(&formula, pf, exp);
    printf("\nPostfix : %s", pf);

    if (!is_legal(pf)){
        printf("\n Exprssion is legal!");
        exit(1);
    }
    ans = calc(&formula, pf);
    printf("\nAnswer : %f", ans);

    return 0;
}



/*
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// ���� ����
typedef struct StackRecord {
    int Top;
    int Stack[MAX]={};
}stackType;

//���� �ʱ�ȭ
void init_stack(stackType* Sptr) {
    Sptr->Top=-1;
}

// �� �ֱ�
int push(stackType* Sptr, int Item) {
    if (Sptr->Top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }
    Sptr->Stack[++(Sptr->Top)] = Item;
    return Item;
}

// �� ����
int pop(stackType* Sptr) {
    if (Sptr->Top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return Sptr->Stack[(Sptr->Top)--];
}

// ���� ���
void print_stack(stackType* Sptr){
    int i;
    printf("\n Stack contents : TOP ----> Bottom\n");
    for (i = Sptr->Top; i >= 0; i--){
        printf("%-6d",Sptr->Stack[i]);
    }
}

// ������ TOP�� ���� �����´�.
int get_stack_top(stackType* Sptr){
    return (Sptr->Top < 0) ? -1 : Sptr->Stack[Sptr->Top];
}

// ������ ����ִ��� �˻�
int is_stack_empty(stackType* Sptr){
    return (Sptr->Top < 0);
}

// k �� ���������� �Ǵ��Ѵ�.
int is_operator(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// ����ǥ��� ������ �����Ѱ� üũ
int is_legal(char *s){
    int f = 0;
    while (*s){
        // ó�� ���� �Ѿ��
        while (*s == ' '){
            s++;
        }

        if (is_operator(*s)){
            f--;
        }
        else{
            f++;
            while (*s != ' '){
                s++;
            }
        }
        if (f < 1) break;
        s++;
    }
    return (f == 1);
}

// �������� �켱������ ��ġ�� ��ȯ���ش�.
int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// ����ǥ����� ����ǥ������� ��ȯ
void postfix(stackType* Sptr, char *dst, char *src){
    char c;
    init_stack(Sptr); //�ʱ�ȭ
    while (*src){
        if (*src == '('){ // '(' �̸� �ֱ�
            push(Sptr,*src);
            src++;
        }
        else if (*src == ')'){ // ')' ������ ���� �迭�� ����
            while (get_stack_top(Sptr) != '('){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            pop(Sptr);
            src++;
        }
        else if (is_operator(*src)){ //������ �� ��
                                    // ������ ������� �ʰ� �켱������ �������� �� ���� �迭�� ����
            while (!is_stack_empty(Sptr) &&
                precedence(get_stack_top(Sptr)) >= precedence(*src)){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            push(Sptr,*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9'){ //�����̸� �ڸ��� Ȯ�� �� �ֱ�
            do{
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else{
            src++;
        }
    }

    while (!is_stack_empty(Sptr)){
        *dst++ = pop(Sptr);
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

// ����ǥ����� ����Ѵ�.
int calc(stackType* Sptr, char *p){
    int i;
    init_stack(Sptr);
    while (*p){
        if (*p >= '0' && *p <= '9'){
            i = 0;
            do{
                i = i * 10 + *p - '0';
                p++;
            } while (*p >= '0' && *p <= '9');
            push(Sptr,i);
        }
        else if (*p == '+'){
            push(Sptr, pop(Sptr) + pop(Sptr));
            p++;
        }
        else if (*p == '*'){
            push(Sptr, pop(Sptr) * pop(Sptr));
            p++;
        }
        else if (*p == '-'){
            i = pop(Sptr);
            push(Sptr, pop(Sptr) - i);
            p++;
        }
        else if (*p == '/'){
            i = pop(Sptr);
            push(Sptr, pop(Sptr) / i);
            p++;
        }
        else{
            p++;
        }
    }
    return pop(Sptr);
}

int main(){
    int ans;
    char exp[256] = "2*3+6/2-4"; //input example!
    char pf[256];
    stackType formula;

    printf("Input the equation: ");
    scanf("%s",exp);

    postfix(&formula, pf, exp);
    printf("\nPostfix : %s", pf);

    if (!is_legal(pf)){
        printf("\n Exprssion is legal!");
        exit(1);
    }
    ans = calc(&formula, pf);
    printf("\nAnswer : %d", ans);

    return 0;
}
*/

