#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// 스텍 선언
typedef struct StackRecord {
    int Top;
    double Stack[MAX]={};
}stackType;

//스텍 초기화
void init_stack(stackType* Sptr) {
    Sptr->Top=-1;
}

// 값 넣기
double push(stackType* Sptr, double Item) {
    if (Sptr->Top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }
    Sptr->Stack[++(Sptr->Top)] = Item;
    return Item;
}

// 값 빼기
double pop(stackType* Sptr) {
    if (Sptr->Top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return Sptr->Stack[(Sptr->Top)--];
}

// 전부 출력
void print_stack(stackType* Sptr){
    int i;
    printf("\n Stack contents : TOP ----> Bottom\n");
    for (i = Sptr->Top; i >= 0; i--){
        printf("%-6f",Sptr->Stack[i]);
    }
}

// 스택의 TOP의 값을 가져온다.
double get_stack_top(stackType* Sptr){
    return (Sptr->Top < 0) ? -1 : Sptr->Stack[Sptr->Top];
}

// 스택이 비어있는지 검사
int is_stack_empty(stackType* Sptr){
    return (Sptr->Top < 0);
}

// k 가 연산자인지 판단한다.
int is_operator(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// 후위표기법 수식이 적합한가 체크
int is_legal(char *s){
    int f = 0;
    while (*s){
        // 처음 공백 넘어가기
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

// 연산자의 우선순위를 수치로 변환해준다.
int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// 중위표기법을 후위표기법으로 변환
void postfix(stackType* Sptr, char *dst, char *src){
    char c;
    init_stack(Sptr); //초기화
    while (*src){
        if (*src == '('){ // '(' 이면 넣기
            push(Sptr,*src);
            src++;
        }
        else if (*src == ')'){ // ')' 만나면 빼서 배열에 저장
            while (get_stack_top(Sptr) != '('){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            pop(Sptr);
            src++;
        }
        else if (is_operator(*src)){ //연산자 일 때
                                    // 스텍이 비어있지 않고 우선순위의 연산자일 때 빼서 배열에 저장
            while (!is_stack_empty(Sptr) &&
                precedence(get_stack_top(Sptr)) >= precedence(*src)){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            push(Sptr,*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9' || *src == '.'){ //숫자이면 자릿수 확인 후 넣기
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

// 후위표기법을 계산한다.
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

// 스텍 선언
typedef struct StackRecord {
    int Top;
    int Stack[MAX]={};
}stackType;

//스텍 초기화
void init_stack(stackType* Sptr) {
    Sptr->Top=-1;
}

// 값 넣기
int push(stackType* Sptr, int Item) {
    if (Sptr->Top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }
    Sptr->Stack[++(Sptr->Top)] = Item;
    return Item;
}

// 값 빼기
int pop(stackType* Sptr) {
    if (Sptr->Top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return Sptr->Stack[(Sptr->Top)--];
}

// 전부 출력
void print_stack(stackType* Sptr){
    int i;
    printf("\n Stack contents : TOP ----> Bottom\n");
    for (i = Sptr->Top; i >= 0; i--){
        printf("%-6d",Sptr->Stack[i]);
    }
}

// 스택의 TOP의 값을 가져온다.
int get_stack_top(stackType* Sptr){
    return (Sptr->Top < 0) ? -1 : Sptr->Stack[Sptr->Top];
}

// 스택이 비어있는지 검사
int is_stack_empty(stackType* Sptr){
    return (Sptr->Top < 0);
}

// k 가 연산자인지 판단한다.
int is_operator(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// 후위표기법 수식이 적접한가 체크
int is_legal(char *s){
    int f = 0;
    while (*s){
        // 처음 공백 넘어가기
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

// 연산자의 우선순위를 수치로 변환해준다.
int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// 중위표기법을 후위표기법으로 변환
void postfix(stackType* Sptr, char *dst, char *src){
    char c;
    init_stack(Sptr); //초기화
    while (*src){
        if (*src == '('){ // '(' 이면 넣기
            push(Sptr,*src);
            src++;
        }
        else if (*src == ')'){ // ')' 만나면 빼서 배열에 저장
            while (get_stack_top(Sptr) != '('){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            pop(Sptr);
            src++;
        }
        else if (is_operator(*src)){ //연산자 일 때
                                    // 스텍이 비어있지 않고 우선순위의 연산자일 때 빼서 배열에 저장
            while (!is_stack_empty(Sptr) &&
                precedence(get_stack_top(Sptr)) >= precedence(*src)){
                *dst++ = pop(Sptr);
                *dst++ = ' ';
            }
            push(Sptr,*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9'){ //숫자이면 자릿수 확인 후 넣기
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

// 후위표기법을 계산한다.
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

